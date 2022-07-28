#ifndef HASH_HPP
#define HASH_HPP

#include <cstdio>
#include <string>
#include <bitset>

#define MAXN 55

class Hash {
	FILE* data, *head;
	int l, p, size, mod;
	int bytesPerRecord;

	struct Record {
		std :: bitset<MAXN> key;
		int nextRecord;
		Record();
		Record(std :: bitset<MAXN>&);
	};		

	int hash(std :: bitset<MAXN>&);

	void expands();

	Record LoadRecord(int);
	void StoreNextRecord(int, int);
	void StoreRecord(Record&, int);

	void new_head();
	int get_head(int);
	void set_head(int, int);

	public:

	Hash();
	~Hash();

	void load(const char*, const char*);

	bool insert(std :: bitset<MAXN>&);
	bool exists(std :: bitset<MAXN>&);
};

#endif
