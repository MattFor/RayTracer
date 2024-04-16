## Getting an output image.
When using powershell, use this command:

`.\cmake-build-debug\RayTracer.exe | Out-File -FilePath "../image_result.ppm" -Encoding ASCII`

Then open the resulting file in XnView f.e

## Attributions
This project was inspired by [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)