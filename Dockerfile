# syntax=docker/dockerfile:1
  
# specify the base image to  be used for the application
FROM alpine:latest
  
# create the working directory in the image
WORKDIR /build
  
# copy source files image
COPY . /build/

RUN apk update

#RUN adduser -D -g users user
#RUN mkdir -p /home/user \
#	&& chown user:users /home/user

RUN apk add --no-cache \
        autoconf automake bash m4 flex bison libtool \
        gettext glib gettext-dev clang musl-dev glib \
        gtk+2.0 gtk+2.0-dev gtk+3.0 gtk+3.0-dev make

RUN apk add --no-cache \
        xvfb x11vnc fluxbox xdpyinfo st vim terminus-font \
	&& sed -r -i "s/\[exec\] \(xterm\) \{xterm\}/\[exec\] \(st\) \{st -f 'xos4 Terminus-14'\}/" /usr/share/fluxbox/menu 
	#&& [[ ! -d /opt ]] && mkdir /opt \
	#&& rm -vrf /var/cache/apk/*

# compile application
RUN ./autogen.sh
RUN CC=clang ./configure --prefix=/usr/local
RUN make -j
RUN make install
#RUN ls src/gtk/gftp

#USER user
#ENV HOME /home/user
#WORKDIR /home/user
#RUN ls src/gtk/gftp
  
# network port at runtime
EXPOSE 5900
  
# execute when the container starts
CMD [ "/build/bootstrap.sh" ]
