generate dataset (python)

python src\generator/generate.py n data/dataset_n.csv 
example :
python src\generator/generate.py 52000000 data/dataset_52000000.csv 
python src\generator/generate.py 66666666 data/dataset_66666666.csv 


sorting step(python)

python src/generator/sorting/merge_sort_step.py data/dataset_n.csv 0 6
python src/generator/sorting/quick_sort_step.py data/dataset_n.csv 0 6
example :
python src/generator/sorting/merge_sort_step.py data/dataset_10000000.csv 0 6
python src/generator/sorting/quick_sort_step.py data/dataset_10000000.csv 0 6

sorting (python)

python src/generator/sorting/merge_sort.py data/dataset_n.csv merge_sort_n.csv
python src/generator/sorting/quick_sort.py data/dataset_n.csv quick_sort_n.csv
example :
python src/generator/sorting/merge_sort.py data/dataset_52000000.csv merge_sort_52000000.csv
python src/generator/sorting/quick_sort.py data/dataset_52000000.csv quick_sort_52000000.csv

binary_search (python)

python src/generator/searching/binary_search_step.py output/merge_sort_n.csv 1745
python src/generator/searching/binary_search.py output/merge_sort_n.csv binary_search_n.txt
example :
python src/generator/searching/binary_search_step.py output/merge_sort_10000000.csv 1745
python src/generator/searching/binary_search.py output/merge_sort_10000000.csv binary_search_10000000.txt

generate dataset (cpp)

./dataset_generator <row_count>
example :
.\cpp\dataset_generator.exe 75000000

sorting step(cpp)

.\cpp\merge_sort_step.exe data\dataset_110000000.csv 0 6
.\cpp\quick_sort_step.exe data\dataset_110000000.csv 0 6

sorting (cpp)

.\cpp\merge_sort.exe data/dataset_199000000.csv
.\cpp\quick_sort.exe data/dataset_199000000.csv

if cannot use this : 
g++ -std=c++17 merge_sort.cpp -o merge_sort
then ./merge_sort data/dataset_80000000.csv


binary_search (python)

.\cpp\binary_search_step.exe cpp_output/merge_sort_dataset_10000000.csv 166975706
.\cpp\binary_search.exe cpp_output/merge_sort_dataset_10000000.csv
