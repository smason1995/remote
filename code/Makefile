remoteDir: remote
	@if [ -d "${HOME}/.config/remote/" ]; \
		then echo "remote directory already exists in .config"; \
	else mkdir ${HOME}/.config/remote; \
	     echo "remote directory created in .config"; \
	fi

remote: dll.o
	gcc --std=c11 -o remote remote.c dll.o

dll.o:
	gcc --std=c11 -c dll.c

clean:
	rm -rf remote dll.o ${HOME}/.config/remote
