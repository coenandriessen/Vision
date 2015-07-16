#include "StudentPreProcessing.h"
#include "basetimer.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	BaseTimer basetimer;
	basetimer.start();


	IntensityImageStudent * output = new IntensityImageStudent();
	output->set(image.getWidth(), image.getHeight());
	for (int i = 0; i < image.getWidth(); i++){
		for (int ii = 0; ii < image.getHeight(); ii++){
			Intensity pixel;
			RGB rgb = image.getPixel(i, ii);
			pixel = ((0.3f * rgb.r) + (0.59f*  rgb.g) + (0.11 * rgb.b));
			output->setPixel(i, ii, pixel);
		}
	}
	basetimer.stop();
	std::ofstream myfile;
	myfile.open("tijd.txt", std::ofstream::ate);
	myfile << "tijds: " << basetimer.elapsedSeconds() << " tijd ms:" << basetimer.elapsedMilliSeconds() << "tijd us" << basetimer.elapsedMicroSeconds();
	myfile.close();
	return output;
	
}
IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {

	return stepScaleImageFirstOrder(image);
}
IntensityImage * StudentPreProcessing::stepScaleImageZeroOrder(const IntensityImage &image) const {
	std::cout << "scale";

	if (image.getHeight()*image.getWidth() > 200 * 200){

		auto scale = sqrt(200*200 / static_cast<double>(image.getWidth() * image.getHeight()));
		IntensityImage* product = new IntensityImageStudent(image.getWidth()*scale, image.getWidth()*scale);

		for (auto Xcord = 0; Xcord < image.getWidth()*scale; ++Xcord)
		{
			for (auto Ycord = 0; Ycord < image.getWidth()*scale; ++Ycord)
			{
				//std::cout << xScale* Xcord << " " << yScale* Ycord << "\n";
				Intensity pixel = image.getPixel(std::round(scale* Xcord), std::round(scale* Ycord));
				product->setPixel(Xcord, Ycord, pixel);


			}
		}
		return product;
	}
	else{ return new IntensityImageStudent(); }
	
}


IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage *product = new IntensityImageStudent(image.getWidth(), image.getHeight());
	int index = 0;
	unsigned char compare = 220;
	for (auto Xcord = 0; Xcord < image.getWidth(); ++Xcord)
	{
		for (auto Ycord = 0; Ycord < image.getHeight(); ++Ycord)
		{
			if (image.getPixel(Xcord, Ycord) > compare)
			{
				product->setPixel(Xcord, Ycord, 0);
			}
			else
			{
				product->setPixel(Xcord, Ycord, 255);
			}
		}
	}
	return product;

}

IntensityImage * StudentPreProcessing::stepScaleImageFirstOrder(const IntensityImage &image) const {
	std::cout << "scale";

	if (image.getHeight()*image.getWidth() > 200 * 200){

		double scale = sqrt(200 * 200 / static_cast<double>(image.getWidth() * image.getHeight()));
		IntensityImage* product = new IntensityImageStudent(image.getWidth()*scale, image.getHeight()*scale);

		for (auto Xcord = 0; Xcord < product->getWidth(); ++Xcord)
		{
			for (auto Ycord = 0; Ycord < product->getHeight(); ++Ycord)
			{
				Intensity pixel1 = image.getPixel(std::floor(Xcord * (1 / scale)), std::floor(Ycord * (1 / scale)));
				Intensity pixel2 = image.getPixel(std::floor(Xcord * (1 / scale)), std::ceil(Ycord * (1 / scale)));
				Intensity pixel3 = image.getPixel(std::ceil(Xcord * (1 / scale)), std::floor(Ycord * (1 / scale)));
				Intensity pixel4 = image.getPixel(std::ceil(Xcord * (1 / scale)), std::ceil(Ycord * (1 / scale)));



				Intensity pixel = (pixel1 + pixel2 + pixel3 + pixel4) / 4;
				product->setPixel(Xcord, Ycord, pixel);


			}
		}

		std::cout << scale << " " << scale << "\n";
		std::cout << product->getHeight() << " " << product->getWidth();
		getchar();
		return product;
	}
	else { std::cout << "fuck"; getchar(); }
}
