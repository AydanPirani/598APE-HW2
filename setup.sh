apt-get -y update && apt-get install -y --no-install-recommends curl gnupg software-properties-common \
    && curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key|apt-key add - \
    && apt-add-repository "deb http://apt.llvm.org/`lsb_release -c | cut -f2`/ llvm-toolchain-`lsb_release -c | cut -f2`-19 main"

apt-get -y install autoconf cmake ninja-build gcc g++ linux-tools-common linux-tools-generic libtool libopenmpi-dev openmpi-bin git make imagemagick ffmpeg libpng-dev libjpeg-dev libtiff-dev libopenmpi-dev openmpi-bin ffmpeg python3 pip valgrind gdb hyperfine cargo

ln -s /usr/bin/convert /usr/bin/magick
