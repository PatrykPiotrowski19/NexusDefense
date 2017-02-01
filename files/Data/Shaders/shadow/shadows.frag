
	uniform sampler2DShadow ShadowMap;
	
	varying vec4 ShadowCoord;
	
	// This define the value to move one pixel left or right
	uniform float xPixelOffset ;
	
	// This define the value to move one pixel up or down
	uniform float yPixelOffset ;
	
	float lookup( vec2 offSet)
	{
		// Values are multiplied by ShadowCoord.w because shadow2DProj does a W division for us.
		return shadow2DProj(ShadowMap, ShadowCoord + 
		                               vec4(offSet.x * xPixelOffset * ShadowCoord.w, 
		                                    offSet.y * yPixelOffset * ShadowCoord.w, 
		                                    0.05, 
		                                    0.0) ).w;
	}
	
	void main()
	{		
		float shadow ;
		
		// Avoid counter shadow
		if (ShadowCoord.w > 1.0)
		{
			float x,y;
			for (y = -1.5 ; y <=1.5 ; y+=1.0)
				for (x = -1.5 ; x <=1.5 ; x+=1.0)
					shadow += lookup(vec2(x,y));
			
			shadow /= 16.0 ;
	
		}
	  	gl_FragColor =	  (shadow+0.2);
	  
	}