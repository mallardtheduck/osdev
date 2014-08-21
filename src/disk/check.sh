sudo losetup /dev/loop0 btos.img
sudo partprobe /dev/loop0
sudo fsck.msdos /dev/loop0p1
sudo losetup -d /dev/loop0
