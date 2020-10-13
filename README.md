# FirstGameOnGC

Attention, ce projet est prévu pour être compilé en utilisant l'ide Clion.
Si vous ne l'avez pas, vous pouvez lancer le fichier MakeGB qui se trouve dans "cmake-build-debug" pour compiler.

Pour le moment, seul Windows est supporter avec les fichiers ".bat" mais les commandes à l'intérieur peuvent être faite manuellement.

Les prérequis pour compilé sont: <br/>
  1- avoir téléchargé et installer SDCC.
    <a href="https://sourceforge.net/projects/sdcc/files/sdcc-win64/">ici pour windows</a>
      ou avec la commande: sudo apt install build-essential sdcc sdcc-libraries pour linux
  
  2- avoir téléchargé gbdk-n (bibliothèque de la Game Boy) avec la commande: git clone https:/github.com/flozz/gbdk-ngit    
    Attention, c'est une bibliothèque spécifique, qui doit être compilé avec la commande Make.    
    ajouter aux variables d'environnement le répertoire "bin" est un plus.      
  
  3- Avoir un émulateur.     
    Je recommande <a href="http:/bgb.bircdorg/#downloads">celui-ci </a> qui est pratique, mais seulement disponible sur Windows.
