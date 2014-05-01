#ifndef _MINISTL_HPP
#define _MINISTL_HPP

#include "scheduler.hpp"

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
            for(unsigned int loop;loop < dataSize;++loop)
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

        const vector<T>& operator= (vector<T> x)
        {
            // use copy and swap idiom.
            // Note the pass by value to initiate the copy
            swap(dataSize, x.dataSize);
            swap(reserved, x.rserved);
            swap(data,     x.data);

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
            swap(data, newData);
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
        bool          empty() const {return dataSize == 0;}

        // Operator[] should NOT check the value of i
        // Add a method called at() that does check i
        const T& operator[] (unsigned i) const      {return data[i];}
        T&       operator[] (unsigned i)            {return data[i];}

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
            if (end > dataSize)
            {   end     = dataSize;
            }
            if (start > end)
            {   start   = end;
            }
            unsigned int dst    = start;
            unsigned int src    = end;
            for(;(src < dataSize) && (dst < end);++dst, ++src)
            {
                // Move Elements down;
                data[dst] = data[src];
            }
            unsigned int count = start - end;
            for(;count != 0; --count)
            {
                // Remove old Elements
                --dataSize;
                // Remember we need to manually call the destructor
                data[dataSize].~T();
            }
        }
        unsigned int begin() const  {return 0;}


}; //class vector

#endif
