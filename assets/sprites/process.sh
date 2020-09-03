# Graphics need to be processed in a special order
# since all sprites share the same palette
grit spritesheet-allies.bmp -W3 -g! -gB8 -p -pT0 -ftb -fh!
grit spritesheet-enemies.bmp -W3 -g! -gB8 -p -pT0 -ftb -fh!
grit super-ace.bmp -W3 -gt -gB8 -gT88FF00 -Mw4 -Mh4 -p! -ftbin -fh!
grit bullet.bmp -W3 -gt -gB8 -gT88FF00 -Mw2 -Mh2 -p! -ftbin -fh!
grit basic-enemy.bmp -W -gt -gB8 -gT88FF00 -Mw2 -Mh2 -p! -ftbin -fh!