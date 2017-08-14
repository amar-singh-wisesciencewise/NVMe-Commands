#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<linux/nvme_ioctl.h>
#include<fcntl.h>
#include<linux/types.h>

#define IDENTIFY_LEN 0x1000



//#define NAMESPACE_IDFY
#define CONTROLLER_IDFY
int main(int argc, char* argv[]){
	if(argc < 2){
		printf("kindly give the device file name\n");
		return 1;
		
	}	
	int fd;
	fd = open(argv[1],O_RDWR);
	if(fd == 0){
		printf("could not open device file\n");
		return 1;
	}else printf("device file opened successfully\n");

	char data[IDENTIFY_LEN];
	for(register int i=0; i<IDENTIFY_LEN;data[i++]=0);
	struct nvme_admin_cmd cmd = {
		.opcode = 0x06,
#ifdef NAMESPACE_IDFY
		.nsid = 1,
#endif
#ifdef CONTROLLER_IDFY
		.nsid = 0,
#endif
		.addr = (int)data,
		.data_len = IDENTIFY_LEN,
#ifdef NAMESPACE_IDFY
		.cdw10 = 0,
#endif
#ifdef CONTROLLER_IDFY
		.cdw10 = 1,
#endif

	};
	

	int ret;

	ret= ioctl(fd,NVME_IOCTL_ADMIN_CMD,&cmd);

	if(ret==0) printf("successful \n");
	else printf("failed %d\n",ret);

#ifdef NAMESPACE_IDFY
	printf("NAMESPACE SIZE(MAX LBA): %lld\n",*((__u64*)data));
	printf("NAMESPACE CAPACITY(ALLOWED LBA - THIN OVERPROVISIONING): %lld\n",*((__u64*)(data+8)));
	printf("NAMESPACE UTILIZATION: %lld\n",*((__u64*)(data+16)));
	if(data[24]&0x1)
		printf("Namespace supports Thin OverProvisioning(NAMESPZE CAPACITY reported may be less than SIZE)\n");
	else printf("Thin Overprovisioning not supported\n");
	printf("NUMBER OF LBA FORMATS: %d\n",(__u8)data[25]);
	printf("FORMATED LBA SIZE: %d\n",(__u8)data[26]);
	printf("LBA FORMATE 0: METADAT SIZE: %d\n", *((__u16*)(data+128)));
	printf("LBA FORMATE 0: LBA DATA SIZE(2^n): %d\n", *((__u8*)(data+130)));
#endif
#ifdef CONTROLLER_IDFY	
//	for(register int i=0;i<IDENTIFY_LEN;printf("%c",data[i++]));
	printf("IDENTIFY DETAILS\n");
//	printf("PCI Vendor ID: %c%c\n", data[0],data[1]);
//	printf("PCI subsystem vendor ID: %c%c\n",data[2],data[3]);
	printf("Serial Number: ");
	for(int i =0; i<20; printf("%c",data[(i++)+4]));
	printf("\n");
	printf("Model Number: ");
	for(int i=0; i<40; printf("%c",data[(i++)+24]) );
	printf("\n");
	printf("Firmware Revision: ");
	for(int i = 0;i<8; printf("%c",data[(i++)+64]));
	printf("\n");
	printf("Maximum data transfer size 2^(in units of CAP.MPSMIN): %d\n", (int)data[77] );
	printf("Submission Queue Entry Size 2^:\n");
	printf("--maximum: %d\t", (int)(data[512]>>4));
	printf("--required: %d\n",(int)(data[512]&0x0f));
	printf("Completion Queue Entry Size 2^:\n");
	printf("--maximum: %d\t", (int)(data[513]>>4));
	printf("--required: %d\n",(int)(data[513]&0x0f));
	printf("Number of Namespaces: %d\n", *( (int* )(data+516)));
	if(data[525]&0x1)
		printf("Volatile Write Cache present\n");
		
	printf("Number of Power States supported: %d\n",(int)data[263]);
#endif
	




return 0;
}
