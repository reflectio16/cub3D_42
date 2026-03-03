


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
				cameraX=2∗x/WIDTH−1

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

