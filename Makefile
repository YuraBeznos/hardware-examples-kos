run-kos-1-1-1-40:
	docker run --volume="`pwd`:/data" -w /data --user user -it --rm kos:1.1.1.40 bash

run-kos-1-2-0-45:
	docker run --volume="`pwd`:/data" -w /data --user user -it --rm kos:1.2.0.45 bash

build-kos-1-1-1-40:
	docker build -f Dockerfile-1.1.1.40 ./ -t kos:1.1.1.40

build-kos-1-2-0-45:
	docker build -f Dockerfile-1.2.0.45 ./ -t kos:1.2.0.45

build:
	./cross-build.sh

build-sim:
	./cross-build-sim.sh

clean:
	rm -rf build
