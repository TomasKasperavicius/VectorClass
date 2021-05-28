#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <algorithm>
#include <iostream>
#include <limits>
#include <iterator>
#include <cmath>
#include <cstring>

template <class T> class Vector
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    //constructors
    Vector(){create();}//create an empty vector
    Vector(size_type count,const T& val){create(count,val);}
    Vector(size_type count){create(count);};
    template<typename InputIt>
    Vector( InputIt first, InputIt last){create(first,last);}
    //copy constructor
    Vector(const Vector &v){create(v.begin(),v.end());}
    Vector(std::initializer_list<T> ilist){create(ilist.begin(),ilist.end());}
    Vector(Vector&& other);
    //assignment operators
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);
    Vector& operator=(std::initializer_list<T> ilist);
    void assign( size_type count, const T& value );
    template< typename InputIt >
    void assign( InputIt first, InputIt last );
    void assign( std::initializer_list<T> ilist );

    //destructor
    ~Vector(){uncreate();}
    
    //Member functions

    //Element access
    //at
    T& at(size_type pos);
    const T& at(size_type pos) const;
    //operator[]
    T& operator[](size_type i){return data[i];}
    const T& operator[](size_type i)const{return data[i];}
    //front
    T& front();
    const T& front() const;
    //back
    T& back();
    const T& back() const;
    //data
    T* Data() { return data;}
    const T* Data() const { return data;}

    //Iterators

    //begin
    iterator begin(){return data;}
    const_iterator begin() const {return data;}
    //rbegin
    iterator rbegin(){return avail;}
    const_iterator rbegin() const {return avail;}
    //end
    iterator end(){return avail;}
    const_iterator end() const {return avail;}
    //rend
    iterator rend(){return data;}
    const_iterator rend() const {return data;}

    //Capacity
    //empty
    bool empty() const{return begin() == end();}//if(begin() == end()){return true;}return false;
    //size
    size_type size()const{return avail-data;}
    //max_size
    size_type max_size()const{return std::numeric_limits<size_t>::max()/int(sizeof(T)*2);}
    //reserve
    void reserve(size_type new_cap);
    //capacity
    size_type capacity() const {return limit-data;}
    //shrink_to_fit
    void shrink_to_fit();

    //Modifiers
    //clear
    void clear();
    //insert
    iterator insert(const_iterator pos, const T& value);//+
    iterator insert(const_iterator pos, T&& value);//+
    iterator insert(const_iterator pos, size_type count,const T& value);//+
    iterator insert(const_iterator pos, std::initializer_list<T> ilist);//+
    template<typename InputIterator> iterator insert(const_iterator pos, InputIterator first, InputIterator last);  //+
    //emplace
    template <typename... Args> iterator emplace(const_iterator pos, Args&& ... args);//+
    //erase
    iterator erase( const_iterator pos );//+
    iterator erase( const_iterator first, const_iterator last );//+
    //push_back funkcija
    void push_back(const T& val)
    {
        if (avail == limit)
        {
            grow();
        }
        unchecked_append(val);
    }
    //emplace_back
    template <typename ... Args> T& emplace_back(Args&& ... args);//+
    //pop_back
    void pop_back();
    //resize
    void resize( size_type count );
    void resize( size_type count, const value_type& value );//+
    //swap
    void swap(Vector<T>& other);//+

    //Non-member functions
    //operator==
    template<typename U> friend bool operator==(const Vector<U>& lhs, const Vector<U>& rhs);
    //operator!=
    template<typename U> friend bool operator!=(const Vector<U>& lhs, const Vector<U>& rhs);
    //operator<
    template<typename U> friend bool operator<(const Vector<U>& lhs, const Vector<U>& rhs);//nepadaryti
    //operator<=
    template<typename U> friend bool operator<=(const Vector<U>& lhs, const Vector<U>& rhs);
    //operator<
    template<typename U> friend bool operator>(const Vector<U>& lhs, const Vector<U>& rhs);
    //operator>=
    template<typename U> friend bool operator>=(const Vector<U>& lhs, const Vector<U>& rhs);
    //std::swap
    template<typename U> friend void swap(Vector<U>& lhs, Vector<U>& rhs);
    
private:
    iterator data;
    iterator limit;
    iterator avail;
    std::allocator<T> alloc;
    //atminties isskyrimas
    void create();
    void create(size_type);
    void create(size_type, const T&);
    void create(const_iterator,const_iterator);
    //template< class InputIt >
    void create(iterator,iterator);
    //atminties atlaisvinimas
    void uncreate();

    //funkcijos reikalingos push_back realizacijai
    void grow();
    void unchecked_append(const T&);
    //atminties isskyrimas
    void reallocate(size_type);
};
template<typename T>
Vector<T>::Vector(Vector&& other)
{
    swap(other);
}
template<typename T>
template< typename InputIt >
void Vector<T>::assign( InputIt first, InputIt last )
{
    Vector<T> a(first, last);
    swap(a);
}
template<typename T>
void Vector<T>::assign(std::initializer_list<T> ilist)
{
    swap(Vector(ilist));
}
template<typename T>
void Vector<T>::assign(size_type count, const T& value )
{
    swap(Vector(count, value));
}
template<typename U> bool operator>=(const Vector<U>& lhs, const Vector<U>& rhs)
{
    return !(lhs < rhs);
}
template<typename U> bool operator<=(const Vector<U>& lhs, const Vector<U>& rhs)
{
    return !(lhs > rhs);
}
template<typename U> bool operator>(const Vector<U>& lhs, const Vector<U>& rhs)
{
    typename Vector<U>::size_type n = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    for (size_t i = 0; i < n; i++)
    {
        if (lhs[i] != rhs[i])
        {
        return lhs[i] > rhs[i];     
        }
    }        
    return lhs.size() > rhs.size();
}
template<typename U> bool operator<(const Vector<U>& lhs, const Vector<U>& rhs)
{
    typename Vector<U>::size_type n = (lhs.size() < rhs.size()) ? lhs.size() : rhs.size();
    for (size_t i = 0; i < n; i++)
    {
        if (lhs[i] != rhs[i])
        {
            return lhs[i] < rhs[i];
        }
    }   
    return lhs.size() < rhs.size();
}

template<typename U>
bool operator!=(const Vector<U>& lhs, const Vector<U>& rhs)
{
    return !(lhs == rhs);
}
template<typename U> bool operator==(const Vector<U>& lhs, const Vector<U>& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
			
	for (size_t i = 0; i < lhs.size(); i++)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
	return true;
}
template<typename U>
void swap(Vector<U>& lhs, Vector<U>& rhs)
{
    lhs.swap(rhs);
}
template<typename T>
void Vector<T>::swap(Vector<T>& other)
{  
    std::swap(limit, other.limit);
    std::swap(avail, other.avail);
    std::swap(data, other.data);
    std::swap(alloc, other.alloc);
}
template<typename T>
void Vector<T>::resize( size_type count )
{
    size_t change = 0;
    if (count > this->size())
    {
        if (count > this->capacity())
        {
            reallocate(count);
        }
        avail+=count-this->size();
    }
    else
    {
         
        for (size_t i = count; i < this->size(); i++)
        {
            alloc.destroy(data+i);
            change++;
        }
        avail-=change;
    }
    
}
template<typename T>
void Vector<T>::resize( size_type count, const value_type& value )
{
    size_t change = 0;
    if (count > this->size())
    {
        if (count > this->capacity())
        {
            reallocate(count);
        }
        for (size_t i = this->size(); i < count; i++)
        {
            alloc.construct(data+i, value);
            change++;
        }
        avail+=change;
    }
    else
    {
         
        for (size_t i = count; i < this->size(); i++)
        {
            alloc.destroy(data+i);
            change++;
        }
        avail-=change;	
    }   
}
template<typename T>
template <typename ... Args> T& Vector<T>::emplace_back(Args&& ... args)
{
    if (this->size() == this->capacity() )
    {
        grow();
    }
    alloc.construct(data + this->size(), std::forward<Args>(args) ...);
    size_type index = avail-data;
    avail++;
    return data[index];
}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase( const_iterator first,const_iterator last )
{
    size_type n = last - first;
    iterator it = &data[first - data];
    iterator tmp = it + n;
    if (n == 0)
    {
        return it;
    }
    for (size_t i = 0; i < n; i++)
    {
        alloc.destroy(first++);
    }     
    memmove(it, tmp, this->size() - (tmp - data));
    avail -= n;
    return it;
   
}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase( const_iterator pos )
{
    iterator it = &data[pos - data];
    alloc.destroy(it);
    //it->~T();
    memmove(it, it + 1, this->size() - (it - data));
    avail--;
    return it;
}
template<typename T>
template<typename InputIterator>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, InputIterator first, InputIterator last)
{
    size_type index = pos - data;
    iterator it = &data[index];
    size_type n = std::distance(first, last);
    if (n == 0)
    {
        return it;
    } 
    if (limit-avail < n)
    {
        reallocate(n);
    }
    it = &data[index];
    memmove(it + n, it, this->size() - (it - data));
    
    avail += n;
    for (size_t i = 0; i < n; i++)
    {
    alloc.construct(it++, *first++);
    }
    return it;
}
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, std::initializer_list<T> ilist)
{
    size_type index = pos - data;
    iterator it = &data[index];
    size_type n = ilist.size();
    if (n == 0)
    {
        return it;
    }
    if (limit-avail < n)
    {

        reallocate(n);
    }
    it = &data[index];
    memmove(it + n, it, this->size() - (it - data));
    avail += n;
    for (const T& elem : ilist)
    {
        alloc.construct(it++, elem);
    }    
    return it;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type count,const T& value)
{
    size_type index = pos - data;
    iterator it = &data[index];
    if (count == 0)
    {
        return it;
    }
    if (this->capacity()-this->size() < count)
    {
        reallocate(count);
    }
    it = &data[index]; 
    iterator tmp = avail-1;
    avail+=count;
    iterator temp_avail = avail-1;
    while (temp_avail!=it+count-1)
    {
        alloc.construct(temp_avail--,*(tmp--));
    }
    for (int i = 0; i < count; i++)
    {
        *it = value;
        it++;
    }
    return it;
    
}
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T&& value)
{
    size_type index = pos - data;
    iterator it = &data[index];
    try
    {
        if (index >= this->capacity())
    {
        throw "Index doesn't exist";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    if (avail == limit)
    {
        grow();
    }
    alloc.construct(avail++,*(avail-1));
    iterator tmp = avail-1;
    it = &data[index];
    while (tmp != it)
    {
        std::swap(*tmp,*(tmp-1));
        tmp--;
    }
    *it = value;
    return it;
}
template <typename T>
typename Vector<T>::iterator Vector<T>::insert( const_iterator pos, const T& value )
{
    size_type index = pos - data;
    iterator it = &data[index];
    try
    {
        if (index >= this->capacity())
    {
        throw "Index doesn't exist";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    if (avail == limit)
    {
        grow();
    }
    alloc.construct(avail++,*(avail-1));
    iterator tmp = avail-1;
    it = &data[index];
    while (tmp != it)
    {
        std::swap(*tmp,*(tmp-1));
        tmp--;
    }
    *it = value;
    return it;
}
template <class T>
void Vector<T>::pop_back()
{
    if(this->empty()==false)
    {
        iterator it = avail;
        alloc.destroy(--it);
        avail--;
    } 
}
template <class T>
template <typename... Args>typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, Args&& ... args)
{
    size_type index = pos - data;
    iterator it = &data[index];
    
    if (this->size()+1 > this->capacity())
    {
        grow();
    }
    it = &data[index];
    memmove(it + 1, it, this->size() - (it - data));
    ++avail;
    alloc.construct(it, std::forward<Args>(args) ...);
    return it;
}
template <class T>
void Vector<T>::clear()
{
    if (data)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
    }
    avail = data;
}
template <class T>
void Vector<T>::shrink_to_fit()
{
    if (this->capacity()!=this->size())
    {
        reallocate(this->size());
    }
}
template <class T>
void Vector<T>::reserve(size_type new_cap)
{
    try
    {
    if(new_cap > this->capacity())
    {
    iterator new_data = alloc.allocate(new_cap);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail; 
    limit = data + new_cap;
    } 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    } 
}
template <class T>
T& Vector<T>::back()
{
    try
    {
    if (this->empty())
    {
        throw "Vector is empty!";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    return data[this->size()-1];
}
template <class T>
const T& Vector<T>::back() const
{
    try
    {
    if (this->empty())
    {
        throw "Vector is empty!";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    return data[this->size()-1];
}
template <class T>
T& Vector<T>::front()
{
    try
    {
    if (this->empty())
    {
       throw "Vector is empty!";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    return data[0];
}
template <class T>
const T& Vector<T>::front() const
{
    try
    {
    if (this->empty())
    {
        throw "Vector is empty!";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    return data[0];
}
template <class T>
T& Vector<T>::at(size_type pos)
{
    try
    {
    if (pos>=this->size())
    {
        throw "Index out of range";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    return data[pos];   
}
template <class T>
const T& Vector<T>::at(size_type pos) const
{
    try
    {
    if (pos>=this->size())
    {
        throw "Index out of range";
    }
    }
    catch(const char* message)
    {
        std::cerr << message << '\n';
        exit(1);
    }
    return data[pos];   
}
template <class T>
Vector<T>& Vector<T>::operator=(const Vector& rhs){
    if (&rhs != this)
    {
        uncreate();
        create(rhs.begin(),rhs.end());
    }
    return *this;
}
template <class T>
Vector<T>& Vector<T>::operator=(Vector&& rhs){
    if (&rhs != this)
    {
        uncreate();
        create(rhs.begin(),rhs.end());
    }
    return *this;
}
template <class T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> ilist){
    if (&ilist != this)
    {
        uncreate();
        create(ilist.begin(),ilist.end());
    }
    return *this;
}
template<class T>
void Vector<T>::create()
{
    data = avail = limit = nullptr;
}
template<class T>
void Vector<T>::create(size_type n)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
}
template<class T>
//template< class InputIt >
void Vector<T>::create(iterator first, iterator last)
{
    size_type count = std::distance(first, last);
    data = alloc.allocate(count);
    limit = avail = std::uninitialized_copy(first, last, data);
}
template<class T>
void Vector<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}
template<class T>
void Vector<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j-i);
    limit = avail = std::uninitialized_copy(i, j, data);
}
template<class T>
void Vector<T>::uncreate()
{
    if (data)
    {
        iterator it = avail;
        while (it != data)
        {
            alloc.destroy(--it);
        }
        alloc.deallocate(data,limit - data);
    }
    data = limit = avail = nullptr;
}
template <class T>
void Vector<T>::grow(){
size_type new_size = std::max(2 * (limit - data), std::ptrdiff_t(1));
iterator new_data = alloc.allocate(new_size);
iterator new_avail = std::uninitialized_copy(data, avail, new_data);
uncreate();
data = new_data;
avail = new_avail; 
limit = data + new_size;
}
template <class T> void Vector<T>::unchecked_append(const T& val) {
 alloc.construct(avail++, val);
}
template <class T>
void Vector<T>::reallocate(size_type n){
    size_type new_size = (n-(limit - avail))+(limit - data);
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    uncreate();
    data = new_data;
    avail = new_avail; 
    limit = data + new_size;
}
#endif
