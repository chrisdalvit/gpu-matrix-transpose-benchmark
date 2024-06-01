rsync -r -e "ssh -i ~/.ssh/marzola" lib/ christian.dalvit@marzola.disi.unitn.it:~/assignment2/lib/
rsync -r -e "ssh -i ~/.ssh/marzola" src/ christian.dalvit@marzola.disi.unitn.it:~/assignment2/src/
rsync -r -e "ssh -i ~/.ssh/marzola" bin/ christian.dalvit@marzola.disi.unitn.it:~/assignment2/bin/
scp -i ~/.ssh/marzola run.sh christian.dalvit@marzola.disi.unitn.it:~/assignment2/
scp -i ~/.ssh/marzola submit*.sh christian.dalvit@marzola.disi.unitn.it:~/assignment2/
scp -i ~/.ssh/marzola Makefile christian.dalvit@marzola.disi.unitn.it:~/assignment2/