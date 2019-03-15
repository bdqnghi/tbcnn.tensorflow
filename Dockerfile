FROM yijun/fast:base
RUN apk update
RUN apk upgrade
RUN apk add --update go gcc g++
WORKDIR /usr/bin
ENV GOPATH /usr/bin
ENV CGO_ENABLED=1
ENV GOOS=linux
RUN addgroup -g 33333 gitpod && \
    adduser -G gitpod -u 33333 -s /bin/bash -D gitpod
RUN chmod g+rw /home && \
    chown -R gitpod:gitpod /home/gitpod && \
    mkdir -p /workspace && \
    chown -R gitpod:gitpod /workspace;
RUN mkdir -p /root && touch /root/dontBreakMyBuild
RUN apk add --update --no-cache --allow-untrusted fast@testing
RUN pip3 install --upgrade pip
RUN pip3 install ggnn
RUN pip3 uninstall -y flatast
RUN pip3 install flatast
RUN pip3 install numpy
RUN pip3 install --upgrade https://storage.googleapis.com/tensorflow/mac/cpu/tensorflow-1.12.0-py3-none-any.whl
ENV HOME=/home/gitpod
ENV GITPOD_HOME /home/gitpod
ENV GITPOD_UID_GID 33333
ENV SHELL /bin/bash
ENV USE_LOCAL_GIT trueWORKDIR $HOME
USER gitpod
