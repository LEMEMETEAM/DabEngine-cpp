#ifndef CACHE_H_
#define CACHE_H_

#include <unordered_map>
#include <string>
#include <list>
#include <memory>

template<int size>
class LRUCache
{
    public:
        typedef std::list<std::pair<std::string, std::shared_ptr<void>>> List;
        typedef typename List::iterator List_iter;
        typedef std::unordered_map<std::string, List_iter> Map;
        typedef typename Map::iterator Map_iter;

    private:
        List m_list;
        Map m_map;
        uint32_t m_current_size;
    
    public:
        LRUCache():m_current_size(0){}
        template<typename T>
        inline void add(std::string name, const T& ref)
        {
            Map_iter miter = _touch(name);
            if(miter != m_map.end())
            {
                _remove(miter);
            }

            m_list.push_front(std::make_pair(name, std::make_shared<T>(ref)));
            List_iter liter = m_list.begin();

            m_map.insert(std::make_pair(name, liter));
            m_current_size += 1;

            while(m_current_size > size)
            {
                liter = m_list.end();
                --liter;
                _remove(liter->first);
            }
        }

        inline void touch(const std::string& key)
        {
            _touch(key);
        }


        inline void* get(std::string name,bool touch = true)
        {
            Map_iter miter = m_map.find(name);
            if(miter == m_map.end()) return NULL;
            if(touch) _touch(name);
            return miter->second->second.get();
        }
        
    private:
        inline Map_iter _touch(const std::string key)
        {
            Map_iter miter = m_map.find(key);
            if(miter == m_map.end()) return miter;
            m_list.splice(m_list.begin(), m_list, miter->second);
            return miter;
        }

        inline void _remove(const Map_iter& miter)
        {
            m_current_size -= 1;
            m_list.erase(miter->second);
            m_map.erase(miter);
        }

        inline void _remove(const std::string& key)
        {
            Map_iter miter = m_map.find(key);
            _remove(miter);
        }
};

#endif