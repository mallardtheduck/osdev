#include "../kernel.hpp"
#define swap(x,y) { x = x + y; y = x - y; x = x - y; }

static void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}


string to_upper(const string &str){
	size_t buflen=str.length()+1;
	char *buf=(char*)malloc(buflen);
	memset(buf, 0, buflen);
	strncpy(buf, str.c_str(), buflen);
	for(size_t i=0; i<buflen; ++i){
		if(buf[i] >= 'a' && buf[i] <= 'z') buf[i]=buf[i]-'a'+'A';
	}
	string ret(buf);
	free(buf);
	return ret;
}

bool starts_with(const string &str, const string &cmp){
	if(cmp.size() > str.size()) return false;
	for(size_t i=0; i<cmp.size(); ++i){
		if(str[i]!=cmp[i]) return false;
	}
	return true;
}

vector<string> split_string(const string &str, const char c){
	vector<string> ret;
	string current;
	for(size_t i=0; i<str.size(); ++i){
		if(str[i]==c && current!=""){
			ret.push_back(current);
			current="";
			
		}else{
			current+=str[i];
		}
	}
	if(current!="") ret.push_back(current);
	return ret;
}
