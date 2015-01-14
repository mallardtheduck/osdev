#ifndef _CIRCULAR_BUFFER_HPP
#define _CIRCULAR_BUFFER_HPP

template <typename T, size_t buffer_size> class circular_buffer{
private:
	T buffer[size];
	volatile size_t buffer_count=0;
	size_t buffer_top=0;

public:
	void add_item(T c){
		if(buffer_count < buffer_size){
			buffer_count++;
			buffer[buffer_top] = c;
			buffer_top++;
			if(buffer_top == buffer_size) buffer_top=0;
		}
	}

	T read_item(){
		if(buffer_count){
			int start=buffer_top-buffer_count;
			if(start < 0) {
				start+=buffer_size;
			}
			buffer_count--;
			return buffer[start];
		}else return 0;
	}

	size_t count(){
		return buffer_count;
	}

	bool full(){
		return buffer_count >= buffer_size;
	}

	size_t max_size(){
		return buffer_size;
	}
};

#endif