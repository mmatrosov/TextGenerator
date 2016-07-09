# TextGenerator
Simple text generator based on Markov's chains

# Build
The project was created with Visual Studio 2015, you can use it to build the sources. However, no Windows-specific stuff was used, so there should be no problem to compile the code with any C++14 conformant compiler.

The project uses boost, tested with version 1.61. If you build with Visual Studio, make sure Windows environment variable `BOOST_DIR` points to boost installation directory.

# Use
Learn through example:

	> TextGenerator.exe --train 3 --gen 200 --chain chain.dat --input "The adventures of sherlock holmes.txt"
	Creating chain...
	Processing file "The adventures of sherlock holmes.txt"... done
	Saving chain to "chain.dat"...
	Reading chain from "chain.dat"...
	Input first 3 words:
	> she did not
	Generating further 200 words:
	and she was the girl who waited in the drawing room which is a household word al
	l over the earth one of the woods picking flowers she states that while she was
	walking in this way my dear mr sherlock holmes you may rely upon my doing so he
	looked very scared and puzzled now that the same thing had come upon my father t
	he young man pulled his chair up and pushed his wet feet out towards the fire th
	ere was a cheetah too perhaps we might find it upon our shoulders at any moment
	be seized and searched and there would be no chance of a husband coming forward
	who would ask for all that it was she had the surest information that of late he
	 had when the fit was on him made use of an opium den in the farthest east of th
	e city branch of one of the most resolute of men rather than i should marry anot
	her woman there are no further particulars and the whole place is in a german sp
	eaking country in bohemia not far from carlsbad remarkable as being the scene of
	 the struggle how cruelly i have misjudged him when
	 
For more information run the executable with no arguments and see the help. You can find some input text files in the `data` directory.
