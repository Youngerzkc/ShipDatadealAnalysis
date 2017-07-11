#!/bin/sh
#get port name

rm -rf portName
#获取港口名字
cut -d ' ' -f 1 ./portNameBase/portInformation >> portName 
rm -rf ./portBlock/*
#创建港口目录
cat portName |while read line  
do  
  echo $line;
  mkdir -p ./portBlock/$line
  touch ./portBlock/$line/file  
done  
#处理ship信息
for file in ./shipInformation/*
   do
            if test -d $file
            then
            echo $file
            else
 	    ./sort $file
	    ./readTxt $file
	    rm -rf build	
	    mkdir build	
	    mkdir -p ./validShipInformation/$file
	    cp data.txt ./validShipInformation/$file/
	    cp speed_zero.txt ./validShipInformation/$file/
	    rm -rf data.txt 
	    mv speed_zero.txt ./build/speed_zero
		cd ./build
	    ../choose_zero_block speed_zero

	    for pack in ../build/*
   		 do
			if test -d $pack
			then
			echo $pack
			else
			../valid_pack $pack
       		fi
   		 done
		cd ..
	    for copyfile in ./build/*
		do
		if test -d $copyfile
		then 
		echo $copyfile
		else
		./merge_pack ./portNameBase/portInformation $copyfile
		#cut -d ' ' -f 5,6 file
		fi
	   done
	   
	    for mergefile in ./portBlock/*
	     do 
	 	if test -d $mergefile
			then 
		echo $mergefile 		
		cat $mergefile/*.txt >>$mergefile/file 
		cut -d ' ' -f 5,6 $mergefile/file>>$mergefile/lastfile
		rm -rf $mergefile/*.txt
		fi
	     done
      fi
   done 
#处理新的数据

# for newfile in  



# for bound in ./portBlock/*
# do
# 	if test -d bound 
# 	   pwd
# 	fi

# done
 








