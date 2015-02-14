VANEGUE Elliot
DESHAIES Christopher


/////////////////// Reponse //////////////////////////
7) Le triangle rouge n'apparaît plus car le triangle magenta le recouvre etant
donné qu'il est le dernier tracé.

9.1) L'option less va lancer le test depth(src) < depth(dst) sur chaque pixel.
Il va donc enlever les pixels strictement inférieur a 1. Or la plus grande profondeur
d'un pixel est 1. Il ne va donc garder que les pixels à 1.

9.2) Le changement de glClearDepth avec la valeur 0 fait apparaitre uniquement les triangles magenta et vert soit les point avec un z>0

9.3) Le resultat de glClearDepth(0.5) s'explique que pour cette figure si sur 3 points d'un triangle on a 1 seul point inférieur au test alors on aura une coupure sur le plan


/////////////////////// Remarque ////////////////////////
Pour la question 25, nous n'avons pas bien compris pourquoi
lorsque nous mettons un nombre negatif du l'axe z, la source lumineuse
se met derriere la vache. Nous pensions que les nombre négatif devait
se retrouver dans le dos de la caméra?