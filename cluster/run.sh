module load cuda/12.1 

nvcc ./src/cuda/cuda_naive.cu -o ./bin/cuda_naive
nvcc ./src/cuda/cuda_tiled.cu -o ./bin/cuda_tiled
gcc ./src/c/naive.c ./lib/src/* -g0 -Wall -O3 -o ./bin/cpu_naive -lm
gcc ./src/c/oblivious128.c ./lib/src/* -g0 -Wall -O3 -o ./bin/cpu_oblivious -lm

chmod +x ./bin/cuda_naive
chmod +x ./bin/cuda_tiled
chmod +x ./bin/cpu_naive
chmod +x ./bin/cpu_oblivious

chmod +x ./cluster/jobs/submit_gpu_naive.sh
chmod +x ./cluster/jobs/submit_gpu_tiled.sh
chmod +x ./cluster/jobs/submit_cpu_naive.sh
chmod +x ./cluster/jobs/submit_cpu_oblivious.sh

mkdir -p ./stats/
for i in 8 9 10 11 12 13 14; do
    sbatch --job-name "christian_dalvit_job" --output="./stats/gpu_naive_${i}.out" --error="./stats/gpu_naive_${i}.err" --partition="edu5" --nodes="1" --gres="gpu:1" --ntasks-per-node="1" --cpus-per-task="1" ./cluster/jobs/submit_gpu_naive.sh ${i}
    sbatch --job-name "christian_dalvit_job" --output="./stats/gpu_tiled_${i}.out" --error="./stats/gpu_tiled_${i}.err" --partition="edu5" --nodes="1" --gres="gpu:1" --ntasks-per-node="1" --cpus-per-task="1" ./cluster/jobs/submit_gpu_tiled.sh ${i}
    sbatch --job-name "christian_dalvit_job" --output="./stats/cpu_naive_${i}.out" --error="./stats/cpu_naive_${i}.err" --partition="edu5" --nodes="1" --gres="gpu:1" --ntasks-per-node="1" --cpus-per-task="1" ./cluster/jobs/submit_cpu_naive.sh ${i}
    sbatch --job-name "christian_dalvit_job" --output="./stats/cpu_oblivious_${i}.out" --error="./stats/cpu_oblivious_${i}.err" --partition="edu5" --nodes="1" --gres="gpu:1" --ntasks-per-node="1" --cpus-per-task="1" ./cluster/jobs/submit_cpu_oblivious.sh ${i}
done