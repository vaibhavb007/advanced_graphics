
light
shadowlight
(
    float intensity = 1,
          samples = 256;
    color lightcolor = 1;
    point from = point "shader" (0,0,-2);
)
{
    illuminate(from)
    {
		Cl = intensity * lightcolor / L.L;
		Cl *= transmission(Ps, from);
	}
}