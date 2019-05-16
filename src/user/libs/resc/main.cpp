#include <util/tinyformat.hpp>
#include "resc.tar.h"
#include "tar.hpp"

#include <sstream>
#include <vector>
#include <string>

#include <libelf.h>
#include <gelf.h>
#include <unistd.h>
#include <fcntl.h>

void output_rescs(std::istream &stream){
	tar::reader rdr(stream);
	while(rdr.contains_another_file()){
		tfm::printf("%s \n", rdr.get_next_file_name());
		rdr.skip_next_file();
	}
}

std::string elf_get_section_name(Elf64_Word offset, Elf *e){
	size_t shidx;
	elf_getshstrndx(e, &shidx);
	return elf_strptr(e, shidx, offset);
}

void output_rescs_from_file(const std::string &filename){
	int fd = open(filename.c_str(), O_RDONLY, 0);
	Elf *e = elf_begin(fd, ELF_C_READ, NULL);
	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	while ((scn = elf_nextscn(e, scn))) {
		gelf_getshdr(scn, &shdr);
		if (shdr.sh_type == SHT_PROGBITS && elf_get_section_name(shdr.sh_name, e) == "resc") {
			/* found the resources, go print it. */
			break;
		}
	}
	if(scn){
		Elf_Data *data = elf_getdata(scn, NULL);
		std::stringstream resc;
		resc.write((char*)data->d_buf, data->d_size);
		resc.seekg(0);
		output_rescs(resc);
		free(data->d_buf);
	}else{
		tfm::printf("File has no resources.\n");
	}
	elf_end(e);
	close(fd);
}

int main(int argc, char **argv){
	elf_version(EV_CURRENT);
	std::vector<std::string> args(argv, argv + argc);
	
	tfm::printf("My resources: \n");
	std::stringstream resc;
	resc.write(resc_data, resc_size);
	resc.seekg(0);
	output_rescs(resc);
	
	std::string filename = args[0];
	if(args.size() > 1) filename = args[1];
	
	tfm::printf("Resources from '%s': \n", filename);
	output_rescs_from_file(filename);
	
	return 0;
}