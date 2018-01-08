/*
The MIT License (MIT)

Copyright (c) 2014 fab-jul

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TAR_HPP
#define TAR_HPP

#include <iostream>
#include <string>

namespace tar
{
        typedef long long unsigned file_size_t;
        extern const int FILE_NAME_LENGTH;

        ////////////////////////////////////////
        // Writing raw data
        ////////////////////////////////////////
        class writer {
                std::ostream& _dst;
        public:
                writer(std::ostream& dst) : _dst(dst) {}
                ~writer() { finish(); }

                // Append the data specified by |data| and |file_size| into the
                // tar file represented by |dst|.
                // In the tar file, the data will be available at |path_in_tar|.
                void put(std::string path_in_tar,
                         char const * const data,
                         const file_size_t data_size);

                // Write empty folder at |path_in_tar|.
                // NOTE: to specify folders for files, just use / in the path
                //       passed to |put()|.
                void put_directory(std::string path_in_tar);

                // Call after everything has been added to the tar represented
                // by |dst| to make it a valid tar file.
                void finish();
        };

        ////////////////////////////////////////
        // Reading raw data
        ////////////////////////////////////////
        class reader {
                std::istream& _inp;
                struct  {
                        std::string file_name;
                        file_size_t file_size;
                } _cached_header_data;
                bool _cached_header_data_valid;
                void _cache_header();
                int _number_of_files;

        public:
                // Constructor, pass input stream |inp| pointing to a tar file.
                reader(std::istream& inp)
                : _inp(inp)
                , _cached_header_data_valid(false)
                , _number_of_files(-1) {}

                // Returns true iff another file can be read from |inp|.
                bool contains_another_file();

                // Returns file name of next file in |inp|.
                std::string get_next_file_name();
                // Returns file size of next file in |inp|. Use to allocate
                // memory for the |read_next_file()| call.
                file_size_t get_next_file_size();

                // Read next file in |inp| to |data|.
                void read_next_file(char * const data);
                // Skip next file in |inp|.
                void skip_next_file();

                // Returns number of files in tar at |inp|.
                int number_of_files();
        };
}

#endif // TAR_HPP

