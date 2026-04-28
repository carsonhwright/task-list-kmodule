# task-list-kmodule
print currently running tasks to the kernel ring buf


## commands for load and remove module
```
sudo insmod build/task-list.ko
sudo rmmod task-list
```

### debug read
`sudo dmesg <-c>`

## Build
`make Makefile`