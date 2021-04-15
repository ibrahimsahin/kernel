#include <stdio.h>


char * file=" \n\
if [ $(whoami) != \"root\" ]; \n\
then \n\
echo \"be root\"\n\
else \n\
 \n\
qemu -kernel bin/kernel -chardev pty,id=mon0 -mon chardev=mon0  -daemonize -vnc none -pidfile pid -chroot /tmp/ 2>tmp \n\
let len=0xA00000; \n\
pts=$(grep \"char device\" tmp | awk '{ print $5; }'); \n\
let mpm=0x$(objdump -D bin/kernel | grep mprintf_memory | awk '{ print $1; }'); \n\
sleep $1 \n\
echo stop > $pts \n\
sleep 1 \n\
tf=\"tmpmem$(date +%s)\" \n\
echo memsave $mpm $len $tf > $pts \n\
sleep 10 \n\
echo quit > $pts \n\
cat /tmp/$tf | tr -d '\\0' > results \n\
rm -f /tmp/$tf \n\
rm tmp -f \n\
rm pid -f \n\
 \n\
 \n\
fi;\n\n";

int main(){ 
    FILE *fp=fopen("evalute","w");
    fprintf(fp,"%s",file);
    fclose(fp);
    return 0;
}
