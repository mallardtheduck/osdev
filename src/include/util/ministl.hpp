#ifndef _MINISTL_HPP
#define _MINISTL_HPP

#if defined(KERNEL_MODULE)
#include <btos_module.h>
#elif !defined(KERNEL)
#error "ministl is for kernel-mode only"
#endif

#include <cstdint>
#include <type_traits>

#pragma GCC diagnostic ignored "-Wunused-parameter"

typedef size_t size_type;

// Because you are avoiding std::
// An implementation of swap
template<typename T>
void swap(T& lhs,T& rhs)
{
    T   tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}


template <typename T>
class vector
{
    private:
        unsigned int dataSize;
        unsigned int reserved;
        T*           data;

    public:
		static const size_t npos=0xFFFFFFFF;
        ~vector()
        {
            for(unsigned int loop = 0; loop < dataSize; ++loop)
            {
                // Because we use placement new we must explicitly destroy all members.
                data[loop].~T();
            }
            free(data);
        }
        vector()
            : dataSize(0)
            , reserved(10)
            , data(NULL)
        {
            reserve(reserved);
        }

        vector(const vector<T> &other)
            : dataSize(0)
            , reserved(other.dataSize)
            , data(NULL)
        {
            reserve(reserved);
            dataSize = reserved;
            for(unsigned int loop=0;loop < dataSize;++loop)
            {
                // Because we are using malloc/free
                // We need to use placement new to add items to the data
                // This way they are constructed in place
                new (&data[loop]) T(other.data[loop]);
            }
        }

        vector(unsigned int init_num)
            : dataSize(0)
            , reserved(init_num)
            , data(NULL)
        {
            reserve(reserved);
            dataSize = reserved;
            for(unsigned int loop;loop < dataSize;++loop)
            {
                // See above
                new (&data[loop]) T();
            }
        }

		void swap(vector<T> &other){
			::swap(dataSize, other.dataSize);
			::swap(reserved, other.reserved);
			::swap(data, other.data);
		}

        const vector<T>& operator= (vector<T> x)
        {
            // use copy and swap idiom.
            // Note the pass by value to initiate the copy
            swap(x);
            return *this;
        }

        void reserve(unsigned int new_size)
        {
            if (new_size < reserved)
            {    return;
            }

            T*  newData = (T*)malloc(sizeof(T) * new_size);
            if (!newData)
            {    panic("STL: Error 2.\n");//throw int(2);
            }

            for(unsigned int loop = 0; loop < dataSize; ++loop)
            {
                // Use placement new to copy the data
                new (&newData[loop]) T(data[loop]);
            }
            ::swap(data, newData);
            reserved    = new_size;

            for(unsigned int loop = 0; loop < dataSize; ++loop)
            {
                // Call the destructor on old data before freeing the container.
                // Remember we just did a swap.
                newData[loop].~T();
            }
            free(newData);
        }

        void push_back(const T &item)
        {
            if (dataSize == reserved)
            {
                reserve(reserved * 2);
            }
            // Place the item in the container
            new (&data[dataSize++]) T(item);
        }

        unsigned int  size() const  {return dataSize;}
		unsigned int  capacity() const {return reserved;}
        bool          empty() const {return dataSize == 0;}

        // Operator[] should NOT check the value of i
        // Add a method called at() that does check i
        const T& operator[] (unsigned i) const      {return data[i];}
        T&       operator[] (unsigned i)            {return data[i];}

		const T& at(unsigned i) const{
			if(i >= dataSize) panic("(VECTOR) Overrun!");
			return data[i];
		}

		T& at(unsigned i){
			if(i >= dataSize) panic("(VECTOR) Overrun!");
			return data[i];
		}

        void insert(unsigned int pos, const T& value)
        {
            if (pos >= dataSize)         { throw int(1);}

            if (dataSize == reserved)
            {
                    reserve(reserved * 2);
            }
            // Move the last item (which needs to be constructed correctly)
            if (dataSize != 0)
            {
                new (&data[dataSize])  T(data[dataSize-1]);
            }
            for(unsigned int loop = dataSize - 1; loop > pos; --loop)
            {
                data[loop]  = data[loop-1];
            }
            ++dataSize;

            // All items have been moved up.
            // Put value in its place
            data[pos]   = value;
        }

        void clear()                                        { erase(0, dataSize);}
        void erase(unsigned int erase_index)                { erase(erase_index,erase_index+1);}
        void erase(unsigned int start, unsigned int end)    /* end NOT inclusive so => [start, end) */
		{
			if (end > dataSize) {
				end = dataSize;
			}
			if (start > end) {
				start = end;
			}
			unsigned int dst = start;
			unsigned int src = end;
			for (; (src < dataSize) /*&& (dst < end)*/; ++dst, ++src) {
				// Move Elements down;
				data[dst] = data[src];
			}
			unsigned int count = end - start;
			for (; count != 0; --count) {
				// Remove old Elements
				--dataSize;
				// Remember we need to manually call the destructor
				data[dataSize].~T();
			}
		}

		unsigned int find(const T &item){
			for(size_t i=0; i<dataSize; ++i){
				if(data[i] == item) return i;
			}
			return npos;
		}
		
		T *begin(){
			return data;
		}
		
		T *end(){
			return data + dataSize;
		}

		T &front(){
			return *data;
		}

		T &back(){
			return data[dataSize - 1];
		}

		const T *begin() const{
			return data;
		}
		
		const T *end() const{
			return data + dataSize;
		}


}; //class vector

template <class T1, class T2> struct pair{
	typedef T1 first_type;
	typedef T2 second_type;
	
	first_type first;
	second_type second;

	pair() : first(), second() {};
	pair(const pair<T1, T2> &other):
		first(other.first),
		second(other.second)
	{}
	pair(const first_type &a, const second_type &b):
		first(a),
		second(b)
	{}
};

template <class T1,class T2>pair<T1,T2> make_pair (T1 x, T2 y)
{ return ( pair<T1,T2>(x,y) ); }

template <class T1, class T2>
  bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
  bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs==rhs); }

template <class T1, class T2>
  bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
  bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>
  bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>
  bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ return !(lhs<rhs); }

template <class Arg1, class Arg2, class Result>
  struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};

template <class T> struct less : binary_function <T,T,bool> {
	bool operator() (const T& x, const T& y) const {return x<y;}
};

template<typename T> class allocator {
public:
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef T value_type;
	template <typename U> struct rebind { typedef allocator<U> other; };
	
	pointer allocate (size_t n, void* hint=0){
		return (pointer)malloc(n*sizeof(value_type));
	}
	void deallocate (pointer p, size_type n){
		free(p);
	}

	size_t max_size() const throw(){
		return (size_t)0xFFFFFFFF;
	}
	void construct ( pointer p, const_reference val ){
		new ((void*)p) value_type (val);
	}
	void destroy (pointer p){
		p->~T();
	}
	pointer address ( reference x ) const{
		return &x;
	}
	const_pointer address ( const_reference x ) const{
		return &x;
	}
};

template <> class allocator<void> {
public:
  typedef void* pointer;
  typedef const void* const_pointer;
  typedef void value_type;
  template <class U> struct rebind { typedef allocator<U> other; };
};

static const size_t map_growth_factor=64;

template < typename _Key, typename _Ty, typename _Cmp = less<_Key>, typename _Alloc = allocator< pair<const _Key, _Ty> > > class map
{
public:
	typedef map<_Key, _Ty, _Cmp, _Alloc> _Myt;
	typedef _Key key_type;
	typedef _Ty mapped_type;
	typedef _Cmp compare_type;
	typedef _Alloc allocator_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type *iterator;
	typedef const value_type *const_iterator;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	map()
	: size_(0), capacity_(map_growth_factor), data_(_Alloc().allocate(capacity_))
	{
	}

	map(const _Myt &_Rhs)
	: size_(_Rhs.size_), capacity_(_Rhs.capacity_), data_(_Alloc().allocate(_Rhs.capacity_))
	{
		int count = 0;
		for (iterator i = &_Rhs.data_[0]; i != &_Rhs.data_[_Rhs.size_]; ++i, ++count)
		{
		    _Alloc().construct(&data_[count], *i);
		}
	}

	~map()
	{
		if (!empty())
		{
		    for (iterator i = begin(); i != end(); ++i)
		    {
				_Alloc().destroy(i);
		    }
		}
		_Alloc().deallocate(data_, capacity_);
	}

	_Myt &insert(const value_type &_Value)
	{
		if (size_ + 1 >= capacity_)
		{
		    reserve(capacity_ + map_growth_factor);
		}
		size_++;
		_Alloc().construct(&data_[size_ - 1], _Value);
		return *this;
	}
	
	void erase(iterator it){
		for(size_t i = 0; i < size_ - (it - begin()); ++i){
			_Alloc().destroy(it + i);
			_Alloc().construct(it + i, it[i + 1]);
		}
		size_--;
	}

	void erase(const key_type &Key){
		if(has_key(Key)){
			for(iterator i=begin(); i!=end(); ++i){
				if(i->first == Key){
					erase(i);
					return;
				}
			}
		}
	}

	bool has_key(const key_type &Key) const
	{
		for (const_iterator i = cbegin(); i != cend(); ++i)
		{
			if (i->first == Key)
			{
			    return true;
			}
		}
		return false;
	}

	mapped_type &operator[](const key_type &Key)
	{
		if (has_key(Key))
		{
		    for (iterator i = begin(); i != end(); ++i)
			{
				if (i->first == Key)
				{
					return i->second;
				}
		    }
		}
		size_type op = size_;
		insert(value_type(Key, mapped_type()));
		return data_[op].second;
	}

	value_type &get(const key_type &Key){
		if (has_key(Key))
		{
			for (iterator i = begin(); i != end(); ++i)
			{
				if (i->first == Key)
				{
					return *i;
				}
			}
		}
		size_type op = size_;
		insert(value_type(Key, mapped_type()));
		return data_[op];
	}

	value_type get(const key_type &Key) const{
		if (has_key(Key))
		{
			for (auto i = begin(); i != end(); ++i)
			{
				if (i->first == Key)
				{
					return *i;
				}
			}
		}
		return value_type();
	}

	_Myt &reserve(size_type _Capacity)
	{
		int count = 0;
		if (_Capacity < capacity_)
		{
		    return *this;
		}
		pointer buf = _Alloc().allocate(_Capacity);
		for (iterator i = begin(); i != end(); ++i, ++count)
		{
		    _Alloc().construct(&buf[count], *i);
		}
		swap(data_, buf);
        size_t oldcapacity = capacity_;
        size_t oldsize=size_;
        capacity_ = _Capacity;
		for (iterator i = &buf[0]; i != &buf[oldsize]; ++i)
		{
		    _Alloc().destroy(i);
		}
		_Alloc().deallocate(buf, oldcapacity);
		return *this;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	size_type size() const
	{
		return size_;
	}
	size_type capacity() const
	{
		return capacity_;
	}

	iterator begin()
	{
		return &data_[0];
	}

	iterator end()
	{
		return &data_[size_];
	}

	const_iterator begin() const
	{
		return &data_[0];
	}

	const_iterator end() const
	{
		return &data_[size_];
	}

	const_iterator cbegin() const
	{
		return &data_[0];
	}

	const_iterator cend() const
	{
		return &data_[size_];
	}

	iterator rbegin(){
		return &data_[size_ - 1];
	}

	iterator rend(){
		intptr_t data_addr = (intptr_t)data_;
		return (iterator)(data_addr - sizeof(value_type));
	}
private:
	size_type size_, capacity_;
	pointer data_;
};

template<typename T> typename std::underlying_type<T>::type to_underlying(T a){
	return static_cast<typename std::underlying_type<T>::type>(a);
}

#endif
