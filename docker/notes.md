## build the image
`docker build -t <any image name> .`


## detached + port map
`docker run -d --name <any_name> -p 8881:8881 <image built>`


## rebuild if dockerfile editted

`docker build --no-cache -t <image_name> .`


## troubleshooting

`docker logs <container id>`


