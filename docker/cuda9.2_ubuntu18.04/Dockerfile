FROM nvidia/cuda:9.0-devel-ubuntu16.04
MAINTAINER Harold

RUN apt-get update && apt-get install -y software-properties-common && \
    apt-get install -y --no-install-recommends \
        build-essential \
        clinfo \
        cmake \
        git \
        libboost-all-dev \
        libfftw3-dev \
        libfontconfig1-dev \
        libfreeimage-dev \
        liblapack-dev \
        liblapacke-dev \
        libopenblas-dev \
        ocl-icd-opencl-dev \
        opencl-headers \
        wget \
        xorg-dev && \
    rm -rf /var/lib/apt/lists/*

# Setting up symlinks for libcuda and OpenCL ICD
RUN ln -s /usr/local/cuda/lib64/stubs/libcuda.so /usr/lib/libcuda.so.1 && \
    ln -s /usr/lib/libcuda.so.1 /usr/lib/libcuda.so && \
    mkdir -p /etc/OpenCL/vendors && \
    echo "libnvidia-opencl.so.1" > /etc/OpenCL/vendors/nvidia.icd && \
    echo "/usr/local/nvidia/lib" >> /etc/ld.so.conf.d/nvidia.conf && \
    echo "/usr/local/nvidia/lib64" >> /etc/ld.so.conf.d/nvidia.conf
ENV PATH=/usr/local/nvidia/bin:/usr/local/cuda/bin:${PATH}

WORKDIR /root

# Build GLFW from source
RUN git clone https://github.com/glfw/glfw.git && \
    cd glfw && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr .. && \
    make -j4 && \
    make install


# AF_DISABLE_GRAPHICS - Environment variable to disable graphics at
# runtime due to lack of graphics support by docker - visit
# http://arrayfire.org/docs/configuring_environment.htm#af_disable_graphics
# for more information
ENV AF_PATH=/opt/arrayfire AF_DISABLE_GRAPHICS=1
ARG COMPILE_GRAPHICS=OFF
RUN git clone --recursive https://github.com/arrayfire/arrayfire.git -b v3.6
RUN cd arrayfire && mkdir build && cd build
WORKDIR /root/arrayfire/build

RUN cmake .. -DCMAKE_INSTALL_PREFIX=/opt/arrayfire-3 \
        -DCMAKE_BUILD_TYPE=Release \
        -DAF_BUILD_CPU=ON \
        -DAF_BUILD_CUDA=ON \
        -DAF_BUILD_OPENCL=ON \
        -DAF_BUILD_UNIFIED=ON \
        -DBUILD_GRAPHICS=${COMPILE_GRAPHICS} \
        -DAF_WITH_NONFREE=OFF \
        -DAF_BUILD_EXAMPLES=OFF \
        -DBUILD_TESTING=OFF \
        -DAF_BUILD_DOCS=OFF \
        -DAF_INSTALL_FORGE_DEV=OFF \
        -DAF_WITH_STATIC_FREEIMAGE=OFF

RUN make -j8 && make install && \
    mkdir -p ${AF_PATH} && ln -s /opt/arrayfire-3/* ${AF_PATH}/ && \
    echo "${AF_PATH}/lib" >> /etc/ld.so.conf.d/arrayfire.conf && \
    echo "/usr/local/cuda/nvvm/lib64" >> /etc/ld.so.conf.d/arrayfire.conf && \
    ldconfig

WORKDIR /root/arrayfire
