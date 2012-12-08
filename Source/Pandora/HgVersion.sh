#!/bin/bash

# Grab the Mercurial version informtaion and store it in a header file
# for the project to use

HGREV=`hg identify -n`
HGREVNOMOD=${HGREV//\+/""}
HGCHANGESET=`hg parents --template "{node}"`
HGCHANGESETSHORT=`hg parents --template "{node|short}"`
declare -i HGLOCALMODIFICATIONS=0
HGHEADER=./Headers/HgVersion.hpp
PROJECT=DAWN

if [[ "$HGREV" == *+ ]]
then
	HGLOCALMODIFICATIONS=1;
else
	HGLOCALMODIFIACTIONS=0;
fi


printf "Revision: $HGREVNOMOD\n"
if [ $HGLOCALMODIFICATIONS == 1 ]
then
	printf "Local modifications made\n";
else
	printf "No local modifications\n";
fi
printf "Changeset: $HGCHANGESET\n\n"
printf "Writing to $HGHEADER..."
printf "#ifndef __" > $HGHEADER
printf "$PROJECT" >> $HGHEADER
printf "_HGVERSION_HPP__\n" >> $HGHEADER
printf "#define __" >> $HGHEADER
printf "$PROJECT" >> $HGHEADER
printf "_HGVERSION_HPP__\n\n" >> $HGHEADER

printf "#define HG_REVISION            $HGREVNOMOD\n" >> $HGHEADER
printf "#define HG_LOCAL_MODIFICATIONS $HGLOCALMODIFICATIONS\n" >> $HGHEADER
printf "#define HG_CHANGESET           \"$HGCHANGESET\"\n" >> $HGHEADER
printf "#define HG_CHANGESET_SHORT     \"$HGCHANGESETSHORT\"\n" >> $HGHEADER

printf "\n#endif\n\n" >> $HGHEADER

printf " Done\n"

