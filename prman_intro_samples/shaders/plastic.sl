surface plastic
(
  float Ks = 0.1;
  float Kd = 0.3;
  float Ka = 0.3, roughness = 0.3;
  color specularcolor = 1
)
{
    normal Nf;
    vector V;

    Nf = faceforward( normalize(N), I );
    V = -normalize(I);

    Oi = Os;
    Ci = Os * ( Cs * color(0.4, 0.7, 0.1) * (Ka*ambient() + Kd*diffuse(Nf)) +
	 	specularcolor * Ks * specular(Nf,V,roughness) );
}
