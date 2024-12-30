## build and save the image
`docker build -t <any image name> .`


## detached mode + port mapping
`docker run -d --name <any_name> -p 8881:8881 <image built>`


## rebuild if dockerfile editted
`docker build --no-cache -t <image_name> .`


## troubleshooting
`docker logs <container id>`


stuff need to test still
- port forwarding from VM to host
- MIGHT test host to public
- Docker compose to deploy all images with configured ports
    - ports can do avail range
    - volume (directory)


2 options for .yaml
1. create new images
2. use existing images to build container