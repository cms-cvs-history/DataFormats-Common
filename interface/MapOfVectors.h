#ifndef Common_MapOfVectors_H
#define Common_MapOfVectors_H

#include <vector>
#include <map>

#include <boost/range/iterator_range.hpp>
#include <boost/range/functions.hpp>

namespace edm {

  /* a linearized read-only map-of vectors

   */
  template<typename K, typename T>
  class MapOfVectors {
  public:
    typedef MapOfVectors<K,T> self;
    typedef std::map<K,std::vector<T> > TheMap;

    typedef std::vector<K> Keys;
    typedef std::vector<size_type> Offsets;
    typedef std::vector<T> Data;
    typedef Keys::const_iterator key_iterator;
    typedef Offsets::const_iterator offset_iterator;
    typedef Data::const_iterator data_iterator;
   
    typedef unsigned int size_type;
    typedef boost::iterator_range<data_iterator> range;

    typedef std::pair<K const, range> Pair;

    class Iter
    : public boost::iterator_facade<Iter,
                                    Pair const, 
                                    boost::forward_traversal_tag >
    {
    
    public:
      typedef Iter self;
      Iter() {}
      
      explicit Iter(key_iterator k, offset_iterator o, std::vector<T> const & d )
	: key(k), 
          off(o),
	  data(d.begin())
      {}
      
    private:
      friend class boost::iterator_core_access;
    
      void increment() {
	++key; ++off; 
      }
      
      bool equal(self const& other) const
      {
	return this->key == other.key;
      }
      
      Pair dereference() const {
	
	return Pair(*k, range(data+(*off),data+(*(off+1)) };
      }

      
      key_iterator key;
      offset_iterator off;
      data_iterator data;
  };




    range emptyRange() const { return range(m_data.end(),m_data.end());}

    MapOfVectors(){}

    MapOfVectors(TheMap const & it) {
      m_keys.reserve(it.size());
      m_offsets.reserve(it.size()+1);
      m_offsets.push_back(0);
      size_type tot=0;
      for(TheMap::const_iterator p=it.begin(); p!=it.end();++p)
	tot += (*p).second.size();
      m_data.reserve(tot);
      for(TheMap::const_iterator p=it.begin(); p!=it.end();++p)
	loadNext((*p).first,(*p).second);

    }
    
    void loadNext(K const & k, std::vector<T> const & v) {
      m_keys.push_back(k);
      m_data.resize(m_offsets.back()+v.size());
      std::copy(v.begin(),v.end(),m_data.begin()+m_offsets.back());
      m_offsets.push_back(m_data.size());
    }

    size_type size() const { return m_keys.size();}
    bool empty() const { return m_keys.empty();}

    key_iterator findKey(K const & k) const {
      std::pair<key_iterator,key_iterator> p =
	std::equal_range(m_keys.begin(), m_keys.end(), k);
      return (p.first!=p.second) ? p.first : m_keys.end();
    }
    
    size_type offset(K const & k) const {
      key_iterator p = findKey(k);
      if (p==m_keys.end()) return m_data.size();
      return m_offsets[p-m_keys.begin()];
    }

    range find(K const & k) const  {
      key_iterator p = findKey(k);
      if (p==m_keys.end()) return emptyRange();
      size_type loc = p-m_keys.begin();
      data_iterator b = m_data.begin()+m_offsets[loc];
      data_iterator e = m_data.begin()+m_offsets[loc+1];
      retrun range(b,e);
    }
    


  private:
    std::vector<K> m_keys;
    std::vector<size_type> m_offsets;
    std::vector<T> m_data;

  };


}

#endif // Common_MapOfVectors_H
