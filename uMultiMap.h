#pragma once
#include <unordered_map>
namespace utl
{


	/*template<typename Key1, typename Key2, typename Val>
	class uMultimap : public std::unordered_map<uint32_t,Val>, public std::unordered_map<Key1, uint32_t>, public std::unordered_map<Key2, uint32_t>
	{
		typedef std::unordered_map<uint32_t, Val> Main_umap;
		typedef std::unordered_map<Key1, uint32_t> K1_umap;
		typedef std::unordered_map<Key2, uint32_t> K2_umap;
	public:
		Val& at(const Key1& key)
		{
			return Main_umap::at(K1_umap::at(key));
		}
		Val& at(const Key2& key)
		{
			Main_umap::at(K2_umap::at(key));
		}
		void insert(Key1 key,Val val)
		{
			uint32_t i = nextInt();
			K1_umap::insert(std::make_pair(key, i));
			Main_umap::insert(std::make_pair(i, val));
		}
		bool insert(Key2 key, Val val)
		{
			
		}
		bool exists(const Key1& key)
		{
			
		}
	private:
		uint32_t nextInt() // get next unique integer
		{
			//quick random generator
			
			static uint32_t x = 123456789, y = 362436069, z = 521288629;
			unsigned long t;
			do{
				x ^= x << 16;
				x ^= x >> 5;
				x ^= x << 1;

				t = x;
				x = y;
				y = z;
				z = t ^ x ^ y;
			} while (Main_umap::find(z) != Main_umap::end())

			return z;
		}
	};*/
}