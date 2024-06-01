module load cuda/12.1 
nvcc src/cuda/cuda_naive.cu -o bin/cuda_naive
chmod +x ./bin/cuda_naive
chmod +x submit_naive.sh
mkdir -p ./stats/
for i in 8 9 10 11 12 13 14; do
    sbatch --job-name "christian_dalvit_job" --output="./stats/naive_${i}.out" --error="./stats/naive_${i}.err" --partition="edu5" --nodes="1" --gres="gpu:1" --ntasks-per-node="1" --cpus-per-task="1" ./submit_naive.sh ${i} | grep -o -E '[0-9]*' >> last_id.txt
done
cat last_id.txt