# PNM_Filters
Written in c++ compiled with g++
Reads a .pnm file and creates a new one with selected filters
USAGE: infile, outfile
To add a filter, initialize it, then call its setInput method to connect it to the pipeline.
For the pipeline to work, it must start with a PNMreader or Color.
For an image to be output, a writer must be used.
