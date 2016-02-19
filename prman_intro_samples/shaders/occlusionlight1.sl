light
occlusionlight1(
  float samples = 64, maxvariation = 0.02;
  color filter = color(1);
  output float __nonspecular = 1;)
{
  normal Ns = normalize(N);

  illuminate (Ps + Ns) { /* force execution independent of light location */
    float occ = occlusion(Ps, Ns, samples, "maxvariation", maxvariation);
    Cl = filter * (1 - occ);
  }
}