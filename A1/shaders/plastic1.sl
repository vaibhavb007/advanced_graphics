surface plastic1
(
  float Ks = 0.5;
  float Kd = 0.5;
  float Ka = 1, roughness = 0.5;
  color specularcolor = 1;
  float samples = 4096, maxvariation = 0.04; string envmap = ""
)
{
    normal Nf;
    vector V;

    Nf = faceforward( normalize(N), I );
    V = -normalize(I);

    Oi = Os;
    Ci = Os * ( Cs * color(0.4, 0.7, 0.4) * (Ka*ambient() + Kd*diffuse(Nf)) +
	 	specularcolor * Ks * specular(Nf,V,roughness) );
    Ci += indirectdiffuse(P, Nf, samples);
}
