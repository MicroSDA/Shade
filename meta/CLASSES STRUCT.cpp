#ROADMAP
v 0.1
containers count: 2 // Shader and models

"Shaders\0":
	type: CONTAINER
	sub_type: ?
	path: "shaders.bin\0"
	//offset: 0x00005 // addres in file 
	dependancy: count -> 1	
		"BasicModel\0":
			type: SHADER
			sub_type: VERTEX
			path: "shaders.bin\0"
			offset: 0x00005 // addres in file 
			dependancy: 0
"Models\0":
	type:CONTAINER
	sub_type: // ?
	path:  ""?
	offset: NULL // Then global container
	dependancy: count -> 2
		"Nanosuit\0": // Class name
			type: PACKET// ?
			sub_type : // ?
			path: "some path" // for example
			offset: NULL // Then global container
			dependancy: count -> 1 // one model for example
				"Model\0": // Class name, will be "Nanousit.Model"
					type:MODEL3D
					sub_type : // ?
					path: "models.bin\0" // for example 
					offset: 0x00001 // just for example
					dependancy: count -> 2 // 3 textures
						"Mesh\0":
							type:MESH // One mesh for example
							sub_type : // ?
							path: "?" // for example 
							offset: NULL // just for example
							dependancy: count -> 4 
								"Diffuse\0": // texture class name, will be "Nanousit.Model.Diffuse" .etc for others
									type: TEXTURE
									sub_type: DIFFUSE
									path: "textures.bin\0" // for example  where
									offset: 0x00002 // addres in file 
									dependancy: 0
								"Specular\0": 
									type: TEXTURE
									sub_type: SPECULAR
									path: "textures.bin\0" // for example  where
									offset: 0x00003 // addres in file 
									dependancy: 0
								"Normal\0": 
									type: TEXTURE
									sub_type: NORMAL
									path: "textures.bin\0" // for example  where
									offset: 0x00004 // addres in file 
									dependancy: 0
						"Shaders.BasicModel\0":
							type: SHADER
							sub_type: ?
							path: "shaders.bin\0"
							offset: 0x00005 // addres in file 
							dependancy: 0 		
						..etc.
		"Nanosuit2\0": // Class name
			type: CONTAINER// ?
			sub_type : // ?
			path: "some path" // for example
			offset: NULL // Then global container
			dependancy: count -> 1 // one model for example
				"Model\0": // Class name, will be "Nanousit.Model"
					type:MODEL3D
					offset: //?
					path: "models.bin\0" // for example 
					addr: 0x00001 // just for example
					dependancy: count -> 1 // 3 textures
						"Mesh\0":
							type:MESH // One mesh for example
							offset: //?
							path: "?" // for example 
							addr: 0x00001 // just for example
							dependancy: count -> 4 
								"Diffuse\0": // texture class name, will be "Nanousit.Model.Diffuse" .etc for others
									type: TEXTURE
									sub_type: DIFFUSE
									path: "textures.bin\0" // for example  where
									offset: 0x00002 // addres in file 
									dependancy: 0
								"Specular\0": 
									type: TEXTURE
									sub_type: SPECULAR
									path: "textures.bin\0" // for example  where
									offset: 0x00003 // addres in file 
									dependancy: 0
								"Normal\0": 
									type: TEXTURE
									sub_type: NORMAL
									path: "textures.bin\0" // for example  where
									offset: 0x00004 // addres in file 
									dependancy: 0
						"BasicModel\0":
							type: SHADER
							sub_type: ?
							path: "shaders.bin\0"
							offset: 0x00005 // addres in file 
							dependancy: 0 		
						..etc.				