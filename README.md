


DIR

	Direction du joueur en fonction de N, S, E, W
		- on retrouve cette info dans la structure player
		- variables dir_x et dir_y

	Where
		- dans fichier init.c
			-fonction direction_init()

	Par convention :
		- x vers la droite
		- y vers le bas

	dir selon orientation
		- E : ( +1, 0 )
		- W : ( -1, 0 )
		- S : ( 0, +1 )
		- N : ( 0, -1 )




PLANE

	Plan perpendiculaire par rapport a la direction du joueur
		- on retrouve cette info dans la structure player
		- variables plane_x et plane_y
		- une variable supplementaire k
			- k est le FOV factor (FOV -> Field Of View)
			- k est une variable constante initialisee a 0.66

	FOV
		Si tu regardes droit devant toi :
			- 30° → vision très étroite (effet zoom)
			- 60° → vision naturelle
			- 120° → effet fish-eye
			- Dans cub3D (style Wolfenstein), on utilise souvent ≈ 60°–66°.
				- c'est pour ca que k = 0.66
	
	Where
		- dans fichier init.c
			-fonction plane_init()

	Calcul a effectuer
			- si dir = (dx, dy)
			- alors plane = (-dy, dx)
		-Explications :
			- On veut un vecteur perpendiculaire à (dx, dy).
				- En 2D, si tu prends :
					(−dy,dx)
				- Ce vecteur est toujours perpendiculaire à (dx, dy).
				- Pourquoi ?
				- Parce que leur produit scalaire vaut 0.
			- Preuve simple :
				- Produit scalaire :
					(dx,dy)*(−dy,dx) = dx(−dy)+dy(dx) = −dxdy+dydx = 0
				Donc ils sont orthogonaux.



CAMERAX

	explication de cameraX :
	
		Si ton écran fait WIDTH pixels :
			- Pour chaque colonne x de l’écran :
				cameraX = 2 ∗ x / WIDTH − 1

		Ça donne :
			- gauche écran → -1
			- centre écran → 0
			- droite écran → +1



DDA - DIGITAL DIFFERENTIAL ANALYZER

	C'est un algorithme qui avance pas a pas dans une grille pour savoir quelle case un rayon va toucher en premier.

		À chaque étape, le DDA doit choisir :
			Est-ce que je traverse une ligne verticale ?
			Ou une ligne horizontale ?



	Calcul de deltaDistX et deltaDistY :

		Si rayDirX = 0.3, ca veut dire que :
			- à chaque unité de distance le long du rayon,
			- x augmente de 0.3 tiles.
		Donc pour que x augmente de 1 tile :
			Combien faut-il avancer ?
				- Si        1 unité → +0.3
				- Alors    cb unité → +1 ?
				- (c'est un simple produit en croix)
			C’est :
				- 1 / 0.3 = 3.33
			Donc :
				- deltaDistX = |1 / rayDirX|

	perpWallDist = Perpendicular Wall Distance

		le calcul :
			perpWallDist = 
				- si on touche un mur vertical : (mapX − posX + (1 − stepX) / 2)​ / 2
							ou
				- si on touche un mur horizontal : (mapY − posY + (1 − stepY) / 2)​ / 2
		
		A quoi ca sert :
			cela corrige l'effet fisheye
				- si un mur est face a nous
				- si on lance un rayon oblique et qu'on lance un rayon droit devant nous
				- le rayon oblique aura parcouru plus de distance que le rayon droit
				- si on ne corrige pas cela avec le perpWallDist
					- le programme aura l'impression que le mur touche par le rayon oblique	
					  est plus loin que le mur touche par le rayon lance droit devant


PLAFOND / MURS / SOL

	Taille d'un mur en hauteur :
		lineHeight = HEIGHT / perpWallDist
			Exemples :
				Si HEIGHT = 1080 :
					perpWallDist = 1.0 → lineHeight = 1080 (mur énorme)
					perpWallDist = 2.0 → lineHeight = 540
					perpWallDist = 4.0 → lineHeight = 270

		drawStart = -lineHeight/2 + HEIGHT/2
			Exemple :
				Imaginons HEIGHT=1080 et lineHeight=540 :
					centre = 540
					moitié = 270
				Donc :
					drawStart = - 270 + 540 = 270
					Le mur commence à y = 270.

		drawEnd = lineHeight/2 + HEIGHT/2
			Exemple :
				toujours avec HEIGHT=1080 et lineHeight=540 :
					centre = 540
					moitié = 270
				Donc :
					drawStart = 270 + 540 = 810
					Le mur finit à y = 810.
