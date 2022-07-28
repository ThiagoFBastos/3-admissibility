#include "hash.hpp"

#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <utility>

const double max_load_factor = 1.0 / 3;

Hash :: Record :: Record() {}

Hash :: Record :: Record(std :: bitset<MAXN>& key) {
	this->key = key;
    nextRecord = -1;
}

Hash :: Hash() {
	data = nullptr;
	head = nullptr;
}

Hash :: ~Hash() {
	if(data) fclose(data);
	if(head) fclose(head);
}

void Hash :: load(const char* filename, const char* headname) {
	l = 0, p = 0, size = 0;
	data = fopen(filename, "w+b");
	head = fopen(headname, "w+b");
	bytesPerRecord = sizeof(unsigned long long) + sizeof(int);
	mod = 454823;

	if(!data) {
		printf("o arquivo %s não foi aberto: %s\n", filename, strerror(errno));
		exit(0);
	}

	if(!head) {
		printf("o arquivo %s não foi aberto: %s\n", headname, strerror(errno));
		exit(0);
	}

	int end = -1;
	for(int i = 1; i <= mod; ++i) fwrite(&end, sizeof(int), 1, head);
}

int Hash :: hash(std :: bitset<MAXN>& key) {
	auto X = key.to_ullong();
	int v = X % (mod << l);
	return v >= p ? v : X % (mod << (l + 1));
}

Hash :: Record Hash :: LoadRecord(int pos) {
	Record r;
	auto key = 0LLU;
	fseek(data, pos * bytesPerRecord, SEEK_SET);
	fread(&key, sizeof(key), 1, data);
	fread(&r.nextRecord, sizeof(int), 1, data);
	r.key = std :: bitset<MAXN>(key);
	return r;
}

void Hash :: StoreRecord(Record& r, int pos) {
	auto key = r.key.to_ullong();
	fseek(data, pos * bytesPerRecord, SEEK_SET);
	fwrite(&key, sizeof(key), 1, data);
	fwrite(&r.nextRecord, sizeof(int), 1, data);
}
	
void Hash :: StoreNextRecord(int nextRecord, int pos) {
	fseek(data, (pos + 1) * bytesPerRecord - sizeof(int), SEEK_SET);
	fwrite(&nextRecord, sizeof(int), 1, data);
}

bool Hash :: insert(std :: bitset<MAXN>& key) {
	
	int h = hash(key), last = -1;
	Record r;
	int end = get_head(h);

	if(end == -1) {
		Record r(key);
		StoreRecord(r, size);
		set_head(h, size++);
	} else {
		
		for(h = end; h != -1; h = r.nextRecord) {	
			r = LoadRecord(h);
			if(key == r.key) return false;
			last = h;
		}
		
		Record r(key);
		StoreNextRecord(size, last);
		StoreRecord(r, size++);
	}

	while(size > max_load_factor * (p + ((mod << l)))) expands();

	return true;
}

bool Hash :: exists(std :: bitset<MAXN>& key) {
	int h = hash(key);
	Record r;
	for(h = get_head(h); h != -1; h = r.nextRecord) {	
		r = LoadRecord(h);
		if(key == r.key) return true;
	}
	return false;
}

void Hash :: expands() {
	int m = mod << l, h, ha = -1, hb = -1;
	Record r;

	new_head();

	h = get_head(p);
	set_head(p, -1);
	
	++p;

	for(; h != -1; h = r.nextRecord) {
		r = LoadRecord(h);
		if(hash(r.key) == p - 1) {
			if(ha != -1) StoreNextRecord(h, ha);
			else set_head(p - 1, h);
			ha = h;
		} else {
			if(hb != -1) StoreNextRecord(h, hb);
			else set_head(p + m - 1, h);
			hb = h;
		}
	}

	if(ha != -1) StoreNextRecord(-1, ha);

	if(hb != -1) StoreNextRecord(-1, hb);

	if(p == m) ++l, p = 0;
}

void Hash :: new_head() {
	int end = -1;
	int m = (mod << l) + p;
	fseek(head, sizeof(int) * m, SEEK_SET);
	fwrite(&end, sizeof(int), 1, head);
}

int Hash :: get_head(int pos) {
	fseek(head, sizeof(int) * pos, SEEK_SET);
	fread(&pos, sizeof(int), 1, head);
	return pos;
}

void Hash :: set_head(int pos, int v) {
	fseek(head, sizeof(int) * pos, SEEK_SET);
	fwrite(&v, sizeof(int), 1, head);
}
