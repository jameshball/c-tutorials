#!/usr/bin/perl
#
#	mfbuild: attempts to build a Makefile for standard normal modular
#		 C code, i.e. every time you #include "fred.h", there may
#		 be a corresponding fred.c file that has to be linked into
#		 the executable.
#		 Originally written in C in the 1990s by me, recoded in Perl
#		 for simplicity and slightly nicer output format in Feb 2016,
#		 also by me, Duncan C. White.

use strict;
use warnings;

use Function::Parameters;
use File::Copy;

my $home = $ENV{HOME};

my $makefile = "Makefile";
my @defs = qw(mfbuilddefs ../mfbuilddefs $home/lib/mfbuilddefs /etc/mfbuilddefs);


#
# copy_file( $infilename, $outfile);
#	Copy the contents of one named file ($infilename) to $outfile.
#
fun copy_file( $infilename, $outfile )
{
	open( my $infile, '<', $infilename ) ||
		die "copy_file: can't open $infilename\n";
	copy( $infile, $outfile ) ||
		die "copy_file: file copying of $infilename failed\n";
	close( $infile );
}


# my $ok = ok_tocreate_makefile( $makefile );
#	Detect whether it's ok to create the $makefile file;
#	it's ok if no $makefile exists, or one exists that was written
#	by mfbuild; otherwise it's not ok.
#	Returns true if ok to create (overwrite).
#
fun ok_tocreate_makefile( $makefile )
{
	return 1 unless -f $makefile;

	open( my $in, '<', $makefile ) ||
		die "mfbuild: can't read existing Makefile to check ".
		    "whether it's ok to overwrite it\n";
	$_ = <$in>;	# read first line
	close( $in );

	return /mfbuild/ ? 1 : 0;
}


#
# my @includes = find_includes( $filename );
#	Find all the "" includes found in a given .c file,
#	return a list of them.
fun find_includes( $filename )
{
	open( my $infile, '<', $filename ) ||		# open .c file
		die "find_includes: can't open $filename\n";

	my @includes;

	while( <$infile> )				# for every line
	{
		chomp;

		if( /^\s*#include\s+"(.+)"/ )		# found an include?
		{
			# append .h filename to include list
			push @includes, $1;
			#print "debug: $filename, found include $1\n";
		}
	}
	close( $infile );

	return @includes;
}


#
# my $str = compile( $cfile, @includes );
#	Generate a Makefile dependency line for a single .o: .c rule,
#	return it as a string.
#
fun compile( $cfile, @includes )
{
	my $ofile = $cfile;
	$ofile =~ s/\.c/.o/;

	# DCW may 2017: only files that exist in the current dir
	my $incstr = join( ' ', grep { -f $_ } @includes );
	return "$ofile:\t$cfile $incstr\n";
}


my @todo;			# C files still todo
my %seen;			# set of every C file we've seen before


#
# update_todo( $cfilename, @includes );
#	ok, so we've parsed $cfilename and found that it includes @includes
#	For every file in @include, convert filename from .h to .c,
#	and add any generated .c files (that we've not yet seen)
#	to the to do list.
#
fun update_todo( $cfilename, @includes )
{
	foreach my $inc (@includes)
	{
		$inc =~ s/\.h$/.c/;		# change .h -> .c

		if( ! $seen{$inc} )		# have not seen this?
		{
			# append .c file name to todo list
			push @todo, $inc;

			# seen it now!
			$seen{$inc}++;
		}	
	}
}


# main program...

die "Usage: mfbuild nameofmainprogram.c\n" unless @ARGV == 1;

my $mainfilename = shift @ARGV;
$mainfilename .= ".c" unless $mainfilename =~ /\.c$/;

@todo = ( $mainfilename );		# put mainfilename onto todo list
$seen{$mainfilename}++;			# mark mainfilename as seen

die "mfbuild: $makefile already exists, not created by mfbuild\n" unless
	ok_tocreate_makefile( $makefile );

open( my $output, '>', $makefile ) || die "mfbuild: can't open $makefile\n";

print $output "# Autogenerated by mfbuild-perl\n\n";
$output->flush();

# copy contents of any project/personal/library defininitions file to Makefile
foreach my $def (@defs)
{
	if( -f $def )	                # found definitions file?
	{
		copy_file( $def, $output );
		last;
	}
}

my $basename = $mainfilename;		# main executable name
$basename =~ s/\.c$//;

my @done;				# C files done, all part of executable

my $rules;				# store all the .o: .c compilation rules

while( @todo )		# more to do
{
	my $filename = shift @todo;

	if( -f $filename )			# .c file found
	{
		my @includes = find_includes( $filename );
		$rules .= compile( $filename, @includes );
		update_todo( $filename, @includes );

		# append .c file name to done
		push @done, $filename;
	}
}

# ok, all file names in done list are part of the program, must be linked.

print $output "BUILD\t=\t$basename\n";

my $outstr = join( ' ', @done );
$outstr =~ s/\.c\b/.o/g;
print $output "OBJS\t=\t$outstr\n\n";

print $output "all:\t\$(BUILD)\n\n";
print $output "clean:\n\t/bin/rm -f \$(BUILD) \$(OBJS) core a.out .nfs*\n\n";

# write link rule to makefile
print $output
	"$basename:\t\$(OBJS)\n".
	"\t\$(CC) \$(CFLAGS) \$(OBJS) \$(LDFLAGS) -o $basename \$(LDLIBS)\n";

# print all the .o: .c compilation rules..
print $output "\n$rules";

close( $output );
exit(0);