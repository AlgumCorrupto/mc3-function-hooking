from typing import List, Tuple

BASE_ADDR = 0x19FF80

with open("./UNPACK_default.iso/FILES/slus_213.55", "rb") as f:
    orig = f.read()
    f.close()

with open("patched.elf", "rb") as f:
    patched = f.read()
    f.close()

changed: List[Tuple[str, str]] = []

size = min(len(orig), len(patched))
for i in range(size):
    if orig[i] != patched[i]:
        changed.append((f"{BASE_ADDR + i:08X}", f"{patched[i]:02X}"))
        # print(changed[-1])

pnach = [
    "gametitle=Midnight Club 3 - DUB Edition (NTSC-U) SLUS-21029 4A0E5B3A v1.0\n",
    "\n",
    "[Digital speedometer (widescreen hud fix]\n",
    "author=AlgumCorrupto\n",
    "description=Speedometer mod that works in the online mode!\n",
    "\n",
]

for change in changed:
    pnach.append(f"patch=0,EE,{change[0]},byte,{change[1]}\n")

with open("60A42FF5.pnach", "w") as f:
    f.writelines(pnach)
    f.close()
