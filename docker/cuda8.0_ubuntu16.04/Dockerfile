FROM arrayfire/arrayfire
MAINTAINER Harold

WORKDIR /usr/test/array-fire

# Ignore APT warnings about not having a TTY
ENV DEBIAN_FRONTEND noninteractive

# Ensure UTF-8 locale
RUN echo "LANG=\"en_GB.UTF-8\"" > /etc/default/locale

# Bundle source
COPY . .

# Config ArrayFire
RUN echo /opt/arrayfire/lib > /etc/ld.so.conf.d/arrayfire.conf
RUN sudo ldconfig
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-8.0/nvvm/lib64/

ENTRYPOINT ["bash"]
