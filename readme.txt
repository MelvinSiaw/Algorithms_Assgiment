<<<<<<< HEAD
generate dataset
python src\generator/generate.py 10000000 data/dataset_10000000.csv 
python src\generator/generate.py 20000000 data/dataset_20000000.csv 
python src\generator/generate.py 30000000 data/dataset_30000000.csv 
python src\generator/generate.py 40000000 data/dataset_40000000.csv 
python src\generator/generate.py 50000000 data/dataset_50000000.csv 
python src\generator/generate.py 60000000 data/dataset_60000000.csv 
python src\generator/generate.py 70000000 data/dataset_70000000.csv 
python src\generator/generate.py 80000000 data/dataset_80000000.csv 
python src\generator/generate.py 90000000 data/dataset_90000000.csv 
python src\generator/generate.py 100000000 data/dataset_100000000.csv 

python part
python src/generator/sorting/merge_sort_step.py data/dataset_10000000.csv 0 6
python src/generator/sorting/quick_sort_step.py data/dataset_10000000.csv 0 6

python src/generator/sorting/merge_sort.py data/dataset_10000000.csv merge_sort_10000000.csv
python src/generator/sorting/quick_sort.py data/dataset_10000000.csv quick_sort_10000000.csv

python src/generator/searching/binary_search_step.py output/merge_sort_10000000.csv 2008864030
python src/generator/searching/binary_search.py output/merge_sort_10000000.csv binary_search_60000000.txt

cpp part
.\cpp\merge_sort_step.exe data\dataset_10000000.csv 0 6
.\cpp\quick_sort_step.exe data\dataset_10000000.csv 0 6

.\cpp\merge_sort.exe data/dataset_10000000.csv
.\cpp\quick_sort.exe data/dataset_10000000.csv

.\cpp\binary_search_step.exe cpp_output/merge_sort_dataset_10000000.csv 166975706
.\cpp\binary_search.exe cpp_output/merge_sort_dataset_10000000.csv
=======
generate dataset
python src\generator/generate.py 10000000 data/dataset_10000000.csv 
python src\generator/generate.py 20000000 data/dataset_20000000.csv 
python src\generator/generate.py 30000000 data/dataset_30000000.csv 
python src\generator/generate.py 40000000 data/dataset_40000000.csv 
python src\generator/generate.py 50000000 data/dataset_50000000.csv 
python src\generator/generate.py 60000000 data/dataset_60000000.csv 
python src\generator/generate.py 70000000 data/dataset_70000000.csv 
python src\generator/generate.py 80000000 data/dataset_80000000.csv 
python src\generator/generate.py 90000000 data/dataset_90000000.csv 
python src\generator/generate.py 100000000 data/dataset_100000000.csv 

python part
python src/generator/sorting/merge_sort_step.py data/dataset_10000000.csv 0 6
python src/generator/sorting/quick_sort_step.py data/dataset_10000000.csv 0 6

python src/generator/sorting/merge_sort.py data/dataset_10000000.csv merge_sort_10000000.csv
python src/generator/sorting/quick_sort.py data/dataset_10000000.csv quick_sort_10000000.csv

python src/generator/searching/binary_search_step.py output/merge_sort_10000000.csv 2008864030
python src/generator/searching/binary_search.py output/merge_sort_10000000.csv binary_search_60000000.txt

cpp part
.\cpp\merge_sort_step.exe data\dataset_10000000.csv 0 6
.\cpp\quick_sort_step.exe data\dataset_10000000.csv 0 6

.\cpp\merge_sort.exe data/dataset_10000000.csv
.\cpp\quick_sort.exe data/dataset_10000000.csv

.\cpp\binary_search_step.exe cpp_output/merge_sort_dataset_10000000.csv 166975706
.\cpp\binary_search.exe cpp_output/merge_sort_dataset_10000000.csv
>>>>>>> c7a7829355377b9b5fbed56673e409158e1ce40f
