# NVMe-Commands
These codes can read and write to NVMe Drive. There are code for sending Controller Identify and Namespace Identify Commands.


THESE CODES HAVE BEEN WRITTEN FOR UBUNTU 16.04 ENVIRONMENT.

"identify_controller.c" program sends an IDENTIFY CONTROLLER Command to an  NVMe Drive and attempt to interpret the data thus returned.
Compiling:  gcc identify_controller.c
Execution: sudo ./a.out /dev/nvme<>

"identify_namespace.c" program sends an IDENTIFY NAMESPACE Command to an NVMe Drive and attempt to interpret the data thus returned.
Compiling:  gcc identify_namespace.c
Execution: sudo ./a.out /dev/nvme<>n<>

"nvme_read.c" program reads the LBAs from NVME DRIVE. Therer are MACROs defined for Sector Count and NAMESPACE, use them.
compiling: gcc nvme_read.c
execution: sudo ./a.out /dev/nvme<>n<>

"nvme_write.c" program writes the LBAs of NVME DRIVE. Therer are MACROs defined for Sector Count and NAMESPACE, use them.
compiling: gcc nvme_read.c
execution: sudo ./a.out /dev/nvme<>n<>


Link to my Blog (for more details and steps involved in coding):
https://wisesciencewise.wordpress.com/category/nvme/
