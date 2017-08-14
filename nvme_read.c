#include<stdio.h>
#include<stdlib.h>
#include<linux/nvme_ioctl.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<time.h>
#include<string.h>



#define SECTORS 2
#define SIZE 512*SECTORS
int main(int argc, char* argv[]){
	int fd = 0;

	struct nvme_passthru_cmd nvme_cmd;
	memset(&nvme_cmd,0,sizeof(nvme_cmd));
	unsigned char buffer[SIZE];
	for(register int i = 0;i<SIZE;buffer[i++]=0);
	int lba;
	printf("what will be the lba:");
	scanf("%d",&lba);
	
	fd = open(argv[1],O_RDWR);

	nvme_cmd.opcode = 0x02;
	nvme_cmd.addr =(unsigned long long*) buffer;
	nvme_cmd.nsid = 1;
	nvme_cmd.data_len = SIZE;
	nvme_cmd.cdw10 = lba;
	nvme_cmd.cdw11 = 0;
	nvme_cmd.cdw12 = SECTORS;
//	nvme_cmd.cdw13 = ;
//	nvme_cmd.cdw14 = ;
//	nvme_cmd.cdw15 = ;
	

	int ret;
	ret = ioctl(fd,NVME_IOCTL_IO_CMD,&nvme_cmd);
	

	if(ret==0)printf("successful\n");
		else printf("failed %d\n",ret); 

	printf("buffer after the read\n");
	for(register int i=0;i<SIZE;printf("%c",buffer[i++]));

return 0;
}
