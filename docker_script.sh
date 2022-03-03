docker build -t study .
docker run -it -v "$PWD":"$PWD" -w "$PWD"/ study
