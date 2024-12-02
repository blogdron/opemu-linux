## OPEMU for Linux for my local experiments

Before use read this

 * https://github.com/mirh/opemu-linux/pull/1

Use original repo, this repo just for my experiments, or take code from this
repo and add it in main repo if you need it :)

### Notice
```diff
- [warning this is experimentall fork, can be broken]
```
 - TODO
   - fix compiler warnings
   - add tests for all instructions
      - maybe use single test by instructtions on assembler
      - maybe use test code contains all test instructions (some other project contains hard SIMD optimisations)

- This is an adaptation of the original Opcode Emulator from [xnu-amd's repo](https://github.com/sinetek/xnu-amd/tree/master/osfmk/OPEMU) for Linux.

- For the kernel module, and a few other things (fpins, SSE4.1...), I took some code from [Meowthra's AVX+ OPEMU](https://www.insanelymac.com/forum/topic/338919-opcode-emulator-opemu-for-linux-64-bit/), which looks pretty good, but does not fit my needs (SSSE3, SSE4.1, & SSE4.2).

- POPCNT and CRC32 are all merit of [Andy Vandijck](https://www.insanelymac.com/forum/topic/281450-mavericks-kernel-testing-on-amd-formerly-mountain-lion-kernel-testing-on-amd/?page=211#comment-1982883) instead.

### Build
```sh
make
```

### Load
```
sudo dmesg -w # open in another terminal window/tab for see logs if need
make load
```
In demesg see output `OPEMU: module loaded` == all okey

Run some `SSE3/SSE4+` application and:
  * if application working `op_emu` success emulate instructions
  * if you see for example `OPEMU:  pminud xmm0, xmm1`
    and `trap invalid opcode` some instruction need implement in `op_emu`
  * if you see only `trap invalid opcode` some instruction unknown for `op_emu`

### Unload
```
make unload
```

## What's working

- SSE3, SSSE3, SSE4.2 (mostly). CRC32 doesn't pass [tests](https://github.com/htot/crc32c) though.
- most SSE4.1 instructions are missing, I tried to add a few but it's not working well yet.
