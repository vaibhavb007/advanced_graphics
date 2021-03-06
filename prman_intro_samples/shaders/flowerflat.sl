surface flowerflat
(
  string texturemap = "textures/flowers_flat.dis";
  float Ks=.1;
  float Kd=.5;
  float Ka=1, roughness=.1;
  color specularcolor=1
)
{
    normal Nf;
    vector V;

    Nf = faceforward( normalize(N), I );
    V = -normalize(I);

    Oi = Os;
    Ci = Os * ( Cs * texture(texturemap, s, t) * (Ka*ambient() + Kd*diffuse(Nf)) +
	 	specularcolor * Ks * specular(Nf,V,roughness) );
}
