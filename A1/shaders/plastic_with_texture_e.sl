surface plastic_with_texture_e
(
  string texturemap = "textures/pebbles.tex";
  float Ks=.7;
  float Kd=.7;
  float Ka=1, roughness=.2;
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
