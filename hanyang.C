void hanyang(){
	TGeoManager *geom = new TGeoManager("geom", "Hanyang University");

// Materials
	TGeoMaterial *Vacuum = new TGeoMaterial("Vacuum", 0, 0, 0);
	TGeoMaterial *Fe = new TGeoMaterial("Fe", 55.845, 26, 7.87);

// Media
	TGeoMedium *Air = new TGeoMedium("Air", 0, Vacuum);
	TGeoMedium *Iron = new TGeoMedium("Iron", 0, Fe);

// Volume
	TGeoVolume *Top = geom->MakeBox("top", Air, 500, 500, 500);
	geom->SetTopVolume(Top);
	geom->SetTopVisible(0);

// Variables
	double sq2 = sqrt(2);
	double pi = M_PI;

	TGeoVolume *cont1;
	TGeoVolume *cont2;

// Ground
	TGeoVolume *ground = geom->MakeBox("gr", Iron, 0.5*400, 0.5*0.5, 0.5*400);
	Top->AddNodeOverlap(ground, 1, new TGeoTranslation(0, -22.5, 0));

// Pillar
	TGeoTranslation *t_up = new TGeoTranslation("t_up", 0, 0, -22.5+1);
	TGeoTranslation *t_down = new TGeoTranslation("t_down", 0, 0, 22.5-2.5);
	t_up->RegisterYourself();
	t_down->RegisterYourself();
	TGeoTube *pillar_body = new TGeoTube("pillar_body", 0, 2, 0.5*45);
	TGeoBBox *up = new TGeoBBox("up", 0.5*5, 0.5*5, 0.5*2);
	TGeoBBox *down= new TGeoBBox("down", 0.5*5, 0.5*5, 0.5*5);
	TGeoCompositeShape *pillar = new TGeoCompositeShape("pillar", "pillar_body+up:t_up+down:t_down");
	TGeoVolume *pillar_vol = new TGeoVolume("pillar_vol", pillar);
	pillar_vol->SetLineColor(10);
	
	for(int i = 0; i < 6; i++)	
		Top->AddNodeOverlap(pillar_vol, 1, new TGeoCombiTrans(-33+67/5*i, 0, 21.8, new TGeoRotation("r1", 0, 90, 0)));

// Balcony
	TGeoVolume *fence_body = geom->MakeTube("fence_body", Iron, 0, 0.25, 0.5*2.2);
	TGeoVolume *fence_side = geom->MakeBox("fence_side", Iron, 0.5*0.6, 0.5*0.6, 0.5*21.8);
	TGeoVolume *fence_main = geom->MakeBox("fence_main", Iron, 0.5*13.4, 0.5*0.6, 0.5*1.2);
	TGeoVolume *bal_ground = geom->MakeBox("bal_ground", Iron, 0.5*13.4*5, 0.5*1.5, 0.5*21.8);

	bal_ground->SetLineColor(17);
	fence_body->SetLineColor(17);
	fence_side->SetLineColor(17);
	fence_main->SetLineColor(17);

	Top->AddNodeOverlap(bal_ground, 1, new TGeoTranslation(0, -22.5+18.2, 10.9));
	Top->AddNodeOverlap(fence_side, 1, new TGeoTranslation(-33, -22.5+20.4, 10));
	Top->AddNodeOverlap(fence_side, 1, new TGeoTranslation(33, -22.5+20.4, 10));

	for(int i = 0; i < 11; i++){
		Top->AddNodeOverlap(fence_body, 1, new TGeoCombiTrans(-33, -22.5+19.3, 0.5+2.23*i, new TGeoRotation("r1", 0, 90, -90)));
		Top->AddNodeOverlap(fence_body, 1, new TGeoCombiTrans(33, -22.5+19.3, 0.5+2.23*i, new TGeoRotation("r1", 0, 90, -90)));
	}
	for(int i = 0; i < 5; i++){
		Top->AddNodeOverlap(fence_main, 1, new TGeoTranslation(-33+6.7+(67/5)*i, -22.5+20.4, 21.5));
		for(int j = 0; j < 7; j++)
			Top->AddNodeOverlap(fence_body, 1, new TGeoCombiTrans(-31+13.4*i+1.56*j, -22.5+19.3, 21.5, new TGeoRotation("r1", 0, 90, -90)));
	}

// Main Deco
	TGeoTranslation *t_deco = new TGeoTranslation("t_deco", 0, 1, 8);
	TGeoTranslation *t_front= new TGeoTranslation("t_front", 0, 0, 11);
	TGeoRotation *r_gr = new TGeoRotation("r_gr", 0, 90, 0);
	t_deco->RegisterYourself();
	t_front->RegisterYourself();
	r_gr->RegisterYourself();

	TGeoArb8 *deco= new TGeoArb8("deco", 3);
	deco->SetVertex(0, 36, 0);
	deco->SetVertex(1, -36, 0);
	deco->SetVertex(2, 0, 20);
	deco->SetVertex(3, 0, 20);
	deco->SetVertex(4, 36, 0);
	deco->SetVertex(5, -36, 0);
	deco->SetVertex(6, 0, 20);
	deco->SetVertex(7, 0, 20);
	TGeoArb8 *deco_front = new TGeoArb8("deco_front", 1);
	deco_front->SetVertex(0, 35, 0);
	deco_front->SetVertex(1, -35, 0);
	deco_front->SetVertex(2, 0, 19.44);
	deco_front->SetVertex(3, 0, 19.44);
	deco_front->SetVertex(4, 32, 0);
	deco_front->SetVertex(5, -32, 0);
	deco_front->SetVertex(6, 0, 19.44);
	deco_front->SetVertex(7, 0, 19.44);
	TGeoBBox *deco_ground = new TGeoBBox("deco_gr", 0.5*70, 0.5*22, 0.5*3);

	TGeoVolume *deco_front_vol = new TGeoVolume("deco_front_vol", deco_front);
	deco_front_vol->SetLineColor(16);

	TGeoCompositeShape *main_deco = new TGeoCompositeShape("main_deco", "deco_gr:r_gr+deco:t_deco-deco_front:t_front");
	TGeoVolume *main_deco_vol = new TGeoVolume("main_deco_vol", main_deco);
	main_deco_vol->SetLineColor(10);
	
	Top->AddNodeOverlap(main_deco_vol, 1, new TGeoTranslation(0, 22.5, 12.5));
	Top->AddNodeOverlap(deco_front_vol, 1, new TGeoTranslation(0, 22.5, 21.6));

// Front Building
	cont1 = geom->MakeBox("main", Iron, 0.5*200, 0.5*45, 0.5*0.5);
	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(0, 0, 0));
	cont1->SetLineColor(17);
	TGeoVolume *bar= geom->MakeBox("bar", Iron, 0.5*2, 0.5*45, 0.5*2);
	bar->SetLineColor(28);
	for(int i = 0; i < 4 ; i++)
		Top->AddNodeOverlap(bar, 1, new TGeoTranslation(-60+40*i, 0, 1));
	Top->AddNodeOverlap(pillar_vol, 1, new TGeoCombiTrans(-33, 0, 0, new TGeoRotation("r1", 0, 90, 0)));
	Top->AddNodeOverlap(pillar_vol, 1, new TGeoCombiTrans(33, 0, 0, new TGeoRotation("r1", 0, 90, 0)));

// Window
	TGeoBBox *window_shape = new TGeoBBox("window_shape", 0.5*4.8, 0.5*7.2, 0.5*0.1);
	
	TGeoVolume *window = geom->MakeBox("window", Iron, 0.5*4.8, 0.5*7.2, 0.5*0.1);
	window->SetLineColor(35);

	for(int i = 0; i < 4; i++){
	double initial_x = -100-4.8;
	double initial_y = 22.5-0.6-0.5*7.2;
		for(int j = 0; j < 20; j++){
			if(j != 0 && j % 4 == 0) initial_x += 2*4.8+2;
			else initial_x += 2*4.8;
			if((i == 2 && j == 2) || (i == 3 && j == 2)) continue;
			Top->AddNodeOverlap(window, 1, new TGeoTranslation(initial_x, initial_y-(4.8+7.2)*i, 0.25));
		}
	}

// Front Side Wall
	TGeoVolume *SideWall = geom->MakeBox("side", Iron, 0.5*21.8, 0.5*45, 0.5*2);
	SideWall->SetLineColor(17);
	cont1 = geom->MakeBox("side1", Iron, 0.5*21.8, 0.5*45, 0.5*2);
	cont2 = geom->MakeBox("side2", Iron, 0.5*21.8, 0.5*45, 0.5*2);
	cont1->AddNodeOverlap(SideWall, 1, new TGeoTranslation(0, 0, 0));
	cont2->AddNodeOverlap(SideWall, 1, new TGeoTranslation(0, 0, 0));
	cont1->AddNodeOverlap(bar, 1, new TGeoTranslation(-10.9+1, 0, 1+0.5));
	cont2->AddNodeOverlap(bar, 1, new TGeoTranslation(10.9-1, 0, 1+0.5));

// Front Side Window
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 2; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(-10.9+4.8+2.4+9.6*j, 22.5-0.6-3.6-12.2*i, 1));
			cont2->AddNodeOverlap(window, 1, new TGeoTranslation(10.9-4.8-2.4-9.6*j, 22.5-0.6-3.6-12.2*i, 1));
		}
	}

	Top->AddNodeOverlap(cont1, 1, new TGeoCombiTrans(-100, 0, 10.9+0.1, new TGeoRotation("r1", 90, 90, 90)));
	Top->AddNodeOverlap(cont2, 1, new TGeoCombiTrans(100, 0, 10.9+0.1, new TGeoRotation("r1", 90, -90, 90)));

// Left & Right Wing
	TGeoVolume *WingWall = geom->MakeBox("wing", Iron, 0.5*40.6, 0.5*45, 0.5*0.05);
	WingWall->SetLineColor(17);
	cont1 = geom->MakeBox("wing", Iron, 0.5*38.6, 0.5*45, 0.5*0.05);
	cont2 = geom->MakeBox("wing", Iron, 0.5*38.6, 0.5*45, 0.5*0.05);
	cont1->AddNodeOverlap(WingWall, 1, new TGeoTranslation(0, 0, 0));
	cont2->AddNodeOverlap(WingWall, 1, new TGeoTranslation(0, 0, 0));
	cont1->AddNodeOverlap(bar, 1, new TGeoTranslation(-19.3+0.5, 0, 0.5));
	cont1->AddNodeOverlap(bar, 1, new TGeoTranslation(19.3-0.5, 0, 0.5));
	cont2->AddNodeOverlap(bar, 1, new TGeoTranslation(-19.3+0.5, 0, 0.5));
	cont2->AddNodeOverlap(bar, 1, new TGeoTranslation(19.3-0.5, 0, 0.5));

// Wing window
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(-19.3+2+0.6+2.4+9.6*j, 22.5-0.6-3.6-12.2*i, 0.05));
			cont2->AddNodeOverlap(window, 1, new TGeoTranslation(19.3-2-0.6-2.4-9.6*j, 22.5-0.6-3.6-12.2*i, 0.05));
		}
	}

	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(-100-1-19.3, 0, 21.8));	
	Top->AddNodeOverlap(cont2, 1, new TGeoTranslation(100+1+19.3, 0, 21.8));	

// Ventilation
	TGeoTranslation *t_ventil_front = new TGeoTranslation("t_ventil_front", 0, 0, 6+0.5);
	t_ventil_front->RegisterYourself();

	TGeoArb8 *tri_pillar = new TGeoArb8("tri_pillar", 6);
	tri_pillar->SetVertex(0, 5, 0);
	tri_pillar->SetVertex(1, -5, 0);
	tri_pillar->SetVertex(2, 0, 7);
	tri_pillar->SetVertex(3, 0, 7);
	tri_pillar->SetVertex(4, 5, 0);
	tri_pillar->SetVertex(5, -5, 0);
	tri_pillar->SetVertex(6, 0, 7);
	tri_pillar->SetVertex(7, 0, 7);

	TGeoArb8 *tri_pillar_cut = new TGeoArb8("tri_pillar_cut", 1);
	tri_pillar_cut->SetVertex(0, 4, 0);
	tri_pillar_cut->SetVertex(1, -4, 0);
	tri_pillar_cut->SetVertex(2, 0, 6);
	tri_pillar_cut->SetVertex(3, 0, 6);
	tri_pillar_cut->SetVertex(4, 4, 0);
	tri_pillar_cut->SetVertex(5, -4, 0);
	tri_pillar_cut->SetVertex(6, 0, 6);
	tri_pillar_cut->SetVertex(7, 0, 6);

	TGeoArb8 *tri_pillar_front = new TGeoArb8("tri_pillar_front", 1);
	tri_pillar_front->SetVertex(0, 4, 0);
	tri_pillar_front->SetVertex(1, -4, 0);
	tri_pillar_front->SetVertex(2, 0, 6);
	tri_pillar_front->SetVertex(3, 0, 6);
	tri_pillar_front->SetVertex(4, 4, 0);
	tri_pillar_front->SetVertex(5, -4, 0);
	tri_pillar_front->SetVertex(6, 0, 6);
	tri_pillar_front->SetVertex(7, 0, 6);

	TGeoVolume *ventil_front = new TGeoVolume("ventil_front", tri_pillar_front);
	ventil_front->SetLineColor(10);

	TGeoCompositeShape *ventil = new TGeoCompositeShape("ventil", "tri_pillar-tri_pillar_cut:t_ventil_front");
	TGeoVolume *ventil_vol = new TGeoVolume("ventil_vol", ventil);
	ventil_vol->SetLineColor(30);
	TGeoVolume *ventil_cont= new TGeoVolume("ventil_cont", ventil);
	ventil_cont->AddNodeOverlap(ventil_vol, 1);
	ventil_cont->AddNodeOverlap(ventil_front, 1, new TGeoTranslation(0, 0.5, 5));
	
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(-85, 22.5+6, -8));
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(-70, 22.5+6, -8));
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(-45, 22.5+6, -8));
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(40, 22.5+6, -8));
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(53, 22.5+6, -8));
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(77, 22.5+6, -8));
	Top->AddNodeOverlap(ventil_cont, 1, new TGeoTranslation(90, 22.5+6, -8));

	TGeoVolume *chimney1 = geom->MakeBox("chimney1", Iron, 0.5*9, 0.5*9, 0.5*15);
	TGeoVolume *chimney2 = geom->MakeBox("chimney2", Iron, 0.5*4, 0.5*4, 0.5*5);
	chimney1->SetLineColor(30);
	chimney2->SetLineColor(17);

	Top->AddNodeOverlap(chimney1, 1, new TGeoCombiTrans(-57, 22.5+9, 0, new TGeoRotation("r1", 0, 90, 0)));
	Top->AddNodeOverlap(chimney2, 1, new TGeoCombiTrans(66, 22.5+8, 2.5, new TGeoRotation("r1", 0, 90, 0)));

// Main Roof
  double angle = 30;
  TGeoRotation *r_face = new TGeoRotation("r_face", 0, -(90-angle), 0);
  TGeoCombiTrans *ct_face = new TGeoCombiTrans("ct_face", 0, 0, -40*cos(angle*pi/180)+1, new TGeoRotation("r1", 0, 90-angle, 0));

  r_face->RegisterYourself();
  ct_face->RegisterYourself();

  TGeoBBox *main_roof_face = new TGeoBBox("main_roof_face", 0.5*202, 0.5*40, 0.5*1);
  TGeoVolume *main_roof_ground= geom->MakeBox("main_roof_gr", Iron, 0.5*202, 0.5*(2*40*cos(angle*pi/180)), 0.5*2);
  main_roof_ground->SetLineColor(10);

  TGeoArb8 *main_roof_tri = new TGeoArb8(2);
  main_roof_tri->SetVertex(0, 35, 0);
  main_roof_tri->SetVertex(1, -35, 0);
  main_roof_tri->SetVertex(2, 0, 20.2);
  main_roof_tri->SetVertex(3, 0, 20.2);
  main_roof_tri->SetVertex(4, 35, 0);
  main_roof_tri->SetVertex(5, -35, 0);
  main_roof_tri->SetVertex(6, 0, 20.2);
  main_roof_tri->SetVertex(7, 0, 20.2);
  TGeoVolume *main_roof_tri_vol = new TGeoVolume("main_roof_tri_vol", main_roof_tri);
  main_roof_tri_vol->SetLineColor(10);

  TGeoCompositeShape *main_roof_shape = new TGeoCompositeShape("main_roof_shape", "main_roof_face:r_face+main_roof_face:ct_face");
  TGeoVolume *main_roof_vol = new TGeoVolume("main_roof_vol", main_roof_shape);
  main_roof_vol->SetLineColor(30);

  Top->AddNodeOverlap(main_roof_ground, 1, new TGeoCombiTrans(0, 22.5+1, -30, new TGeoRotation("r1", 0, 90, 0)));
  Top->AddNodeOverlap(main_roof_vol, 1, new TGeoTranslation(0, 22.5+11, -13));
  Top->AddNodeOverlap(main_roof_tri_vol, 1, new TGeoCombiTrans(-100+2, 22.5, -20-10, new TGeoRotation("r1", -90, 90, 90)));
  Top->AddNodeOverlap(main_roof_tri_vol, 1, new TGeoCombiTrans(100-2, 22.5, -20-10, new TGeoRotation("r1", -90, 90, 90)));

	for(int i = 0; i < 10; i++)
		Top->AddNodeOverlap(ventil_cont, 1, new TGeoCombiTrans(100-12-20*i, 22.5+6, -52, new TGeoRotation("r1", 90, 180, -90)));

// Wing Roof
	TGeoVolume *wing_roof_ground_1 = geom->MakeBox("w_gr_1", Iron, 0.5*44, 0.5*64, 0.5*2);
	TGeoVolume *wing_roof_ground_2 = geom->MakeBox("w_gr_2", Iron, 0.5*20, 0.5*44, 0.5*2);
	wing_roof_ground_1->SetLineColor(10);
	wing_roof_ground_2->SetLineColor(10);

	TGeoTranslation *t1 = new TGeoTranslation("t1", 0, 0, -20);
  TGeoTranslation *t2 = new TGeoTranslation("t2", 0, 0, 30);
  TGeoCombiTrans *ct1 = new TGeoCombiTrans("ct1", 10.5, 0, -10.5, new TGeoRotation("r1", -90, 90, 90));
  TGeoCombiTrans *ct2 = new TGeoCombiTrans("ct2", -10.5, 0, -9.5, new TGeoRotation("r2", -90, -90, 90));
  TGeoCombiTrans *ct3 = new TGeoCombiTrans("ct3", 20, 0.5, -9, new TGeoRotation("r3", 90, 90, -90));
  t1->RegisterYourself();
  t2->RegisterYourself();
  ct1->RegisterYourself();
  ct2->RegisterYourself();
  ct3->RegisterYourself();

  cont1 = geom->MakeBox("wing_roof_container", Iron, 0.5*42, 0.5*42, 0.5*60);
  cont2 = geom->MakeBox("wing_roof_container", Iron, 0.5*62, 0.5*42, 0.5*60);

  TGeoArb8 *wing_roof= new TGeoArb8("wing_roof", 30);
  wing_roof->SetVertex(0, 21, 0);
  wing_roof->SetVertex(1, -21, 0);
  wing_roof->SetVertex(2, 0, 21);
  wing_roof->SetVertex(3, 0, 21);
  wing_roof->SetVertex(4, 21, 0);
  wing_roof->SetVertex(5, -21, 0);
  wing_roof->SetVertex(6, 0, 21);
  wing_roof->SetVertex(7, 0, 21);

  TGeoArb8 *roof_cut = new TGeoArb8("roof_cut", 1);
  roof_cut->SetVertex(0, 20, 0);
  roof_cut->SetVertex(1, -20, 0);
  roof_cut->SetVertex(2, 0, 20);
  roof_cut->SetVertex(3, 0, 20);
  roof_cut->SetVertex(4, 20, 0);
  roof_cut->SetVertex(5, -20, 0);
  roof_cut->SetVertex(6, 0, 20);
  roof_cut->SetVertex(7, 0, 20);

  TGeoArb8 *wing_add_1 = new TGeoArb8("wing_add_1", 10.5);
  wing_add_1->SetVertex(0, 21, 0);
  wing_add_1->SetVertex(1, -21, 0);
  wing_add_1->SetVertex(2, 0, 21);
  wing_add_1->SetVertex(3, 0, 21);
  wing_add_1->SetVertex(4, 20, 21);
  wing_add_1->SetVertex(5, 0, 21);
  wing_add_1->SetVertex(6, 0, 21);
  wing_add_1->SetVertex(7, 0, 21);

	TGeoArb8 *wing_add_2 = new TGeoArb8("wing_add_2", 20);
	wing_add_2->SetVertex(0, 21, 0);
	wing_add_2->SetVertex(1, -21, 0);
	wing_add_2->SetVertex(2, 0, 21);
	wing_add_2->SetVertex(3, 0, 21);
	wing_add_2->SetVertex(4, 21, 0);
	wing_add_2->SetVertex(5, -21, 0);
	wing_add_2->SetVertex(6, 21, 0);
	wing_add_2->SetVertex(7, -21, 0);

	TGeoVolume *roof_cut_vol = new TGeoVolume("roof_cut", roof_cut);
	roof_cut_vol->SetLineColor(10);

  TGeoCompositeShape *cs1 = new TGeoCompositeShape("cs1", "wing_roof-wing_add_1:t1-roof_cut:t2+wing_add_1:ct1");
  TGeoCompositeShape *cs2 = new TGeoCompositeShape("cs2", "wing_roof-wing_add_1:t1-roof_cut:t2+wing_add_1:ct2+wing_add_2:ct3");
  TGeoVolume *cutvol1 = new TGeoVolume("cutvol1", cs1);
  TGeoVolume *cutvol2 = new TGeoVolume("cutvol2", cs2);
	cutvol1->SetLineColor(30);
	cutvol2->SetLineColor(30);

  cont1->AddNodeOverlap(cutvol1, 1);
  cont2->AddNodeOverlap(cutvol2, 1);
	cont1->AddNodeOverlap(wing_roof_ground_1, 1, new TGeoCombiTrans(0, 0, 0, new TGeoRotation("r1", 0, 90, 0)));
	cont2->AddNodeOverlap(wing_roof_ground_1, 1, new TGeoCombiTrans(0, 0, 0, new TGeoRotation("r1", 0, 90, 0)));
	cont2->AddNodeOverlap(wing_roof_ground_2, 1, new TGeoCombiTrans(32, 0, -10, new TGeoRotation("r1", 0, 90, 0)));
	cont1->AddNodeOverlap(roof_cut_vol, 1, new TGeoTranslation(0, 0, 29));
	cont2->AddNodeOverlap(roof_cut_vol, 1, new TGeoTranslation(0, 0, 29));

	cont1->AddNodeOverlap(ventil_cont, 1, new TGeoCombiTrans(-10.3, 5, -10, new TGeoRotation("r1", -90, 90, 90)));
	cont1->AddNodeOverlap(ventil_cont, 1, new TGeoCombiTrans(-10.3, 5, 10, new TGeoRotation("r1", -90, 90, 90)));
	cont2->AddNodeOverlap(ventil_cont, 1, new TGeoCombiTrans(20, 4, -15, new TGeoRotation("r1", -90, 90, 90)));
	cont2->AddNodeOverlap(ventil_cont, 1, new TGeoCombiTrans(20, 4, -5, new TGeoRotation("r1", -90, 90, 90)));
	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(-100-20.3, 23.5, -5));
	Top->AddNodeOverlap(cont2, 1, new TGeoTranslation(100+20.3, 23.5, -5));

// Wing Roof window
	TGeoTranslation *t_wing_window_1 = new TGeoTranslation("t_wing_window_1", 0, -4, 0);
	TGeoTranslation *t_wing_window_2 = new TGeoTranslation("t_wing_window_2", 0, -2, 0);
  t_wing_window_1->RegisterYourself();
  t_wing_window_2->RegisterYourself();
  TGeoTube *wing_window1 = new TGeoTube("wing_window1_1", 0, 4, 0.5*1);
  TGeoBBox *wing_window2 = new TGeoBBox("wing_window2_1", 0.5*8, 0.5*8, 0.5*1);

  TGeoCompositeShape *wing_window_shape = new TGeoCompositeShape("wing_window_shape", "wing_window1_1+wing_window2_1:t_wing_window_1");
  TGeoVolume *wing_window_vol= new TGeoVolume("wing_window_vol", wing_window_shape);
  wing_window_vol->SetLineColor(7);

  Top->AddNodeOverlap(wing_window_vol, 1, new TGeoTranslation(-100-20.3, 22.5+10.5, 24.7));
  Top->AddNodeOverlap(wing_window_vol, 1, new TGeoTranslation(100+20.3, 22.5+10.5, 24.7));

	wing_window1 = new TGeoTube("wing_window1_2", 0, 2, 0.5*1);
	wing_window2 = new TGeoBBox("wing_window2_2", 0.5*4, 0.5*4, 0.5*1);

  wing_window_shape = new TGeoCompositeShape("wing_window_shape", "wing_window1_2+wing_window2_2:t_wing_window_2");
	wing_window_vol = new TGeoVolume("wing_window_vol", wing_window_shape);
  wing_window_vol->SetLineColor(7);

	Top->AddNodeOverlap(wing_window_vol, 1, new TGeoTranslation(-100-10, 22.5+6.5, 24.7));
	Top->AddNodeOverlap(wing_window_vol, 1, new TGeoTranslation(-100-30, 22.5+6.5, 24.7));
	Top->AddNodeOverlap(wing_window_vol, 1, new TGeoTranslation(100+10, 22.5+6.5, 24.7));
	Top->AddNodeOverlap(wing_window_vol, 1, new TGeoTranslation(100+30, 22.5+6.5, 24.7));

// Left Wing Wall
	TGeoVolume *leftside_wall = geom->MakeBox("leftside_wall", Iron, 0.5*60, 0.5*45, 0.5*0.5);
	leftside_wall->SetLineColor(17);
	cont1 = geom->MakeBox("leftside_wall", Iron, 0.5*60, 0.5*45, 0.5*0.5);
	cont1->SetLineColor(17);

	cont1->AddNodeOverlap(leftside_wall, 1);
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 4; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(-17.5+12.5*j, -18.3+18.3*i, -0.5));
		}
	}
	Top->AddNodeOverlap(cont1, 1, new TGeoCombiTrans(-100-40.6, 0, -5, new TGeoRotation("r1", 90, 90, 90)));

	leftside_wall = geom->MakeBox("leftside_wall", Iron, 0.5*40.6, 0.5*45, 0.5*0.5);
	leftside_wall->SetLineColor(17);
	cont1= geom->MakeBox("leftside_wall", Iron, 0.5*40.6, 0.5*45, 0.5*0.5);
	cont1->AddNodeOverlap(leftside_wall, 1);
	cont1->AddNodeOverlap(window, 1, new TGeoTranslation(20.3-5, 22.5-1.5-3.6, -0.5));
	cont1->AddNodeOverlap(window, 1, new TGeoTranslation(20.3-5, 22.5-1.5-3.6-15, -0.5));
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(-20.3-3+6.8*(j+1), 22.5-1.5-3.6-15*i, -0.5));
		}
	}
	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(-100-20.3, 0, -35));

	leftside_wall = geom->MakeBox("leftside_wall", Iron, 0.5*40, 0.5*45, 0.5*0.5);
	leftside_wall->SetLineColor(17);
	cont1 = geom->MakeBox("leftside_wall", Iron, 0.5*20, 0.5*45, 0.5*0.5);
	cont1->AddNodeOverlap(leftside_wall, 1);
	Top->AddNodeOverlap(cont1, 1, new TGeoCombiTrans(-100-1, 0, -42, new TGeoRotation("r1", 90, 90, 90)));

// Rear Wall
	TGeoVolume *rear_wall = geom->MakeBox("rear_wall", Iron, 0.5*202, 0.5*45, 0.5*0.5);
	rear_wall->SetLineColor(17);
	cont1 = geom->MakeBox("rear_wall", Iron, 0.5*202, 0.5*45, 0.5*0.5);
	cont1->AddNodeOverlap(rear_wall, 1);

  TGeoTranslation *t_flag_1 = new TGeoTranslation("t_flag_1", 0, 2.4, 0);
  TGeoTranslation *t_flag_2 = new TGeoTranslation("t_flag_2", 0, -2.4, 0);
  t_flag_1->RegisterYourself();
  t_flag_2->RegisterYourself();
  TGeoTube *tb = new TGeoTube("tb", 0, 0.2, 0.5*2);
  TGeoBBox *box = new TGeoBBox("box", 0.5*0.2, 0.5*4.8, 0.5*1.8);
  TGeoCompositeShape *flag_shape = new TGeoCompositeShape("flag_shape", "box+tb:t_flag_1+tb:t_flag_2");

  TGeoVolume *flag = new TGeoVolume("flag", flag_shape);
	TGeoVolume *pipe = geom->MakeTube("pipe", Iron, 0, 0.5, 0.5*45);
	flag->SetLineColor(kBlue);
	pipe->SetLineColor(1);

  for(int i = 1; i <= 14; i++){
    if(i % 6 == 1){
			flag->SetLineColor(4);
			cont1->AddNodeOverlap(flag, 1, new TGeoTranslation(-7+101-6-2.4-14*i, 22.5-1.5-3.6-15.15, -0.5));
		}
    if(i % 6 == 4){
			flag->SetLineColor(17);
			cont1->AddNodeOverlap(flag, 1, new TGeoTranslation(-7+101-6-2.4-14*i, 22.5-1.5-3.6-15.15, -0.5));
		}
		if(i % 3 == 1)
			cont1->AddNodeOverlap(pipe, 1, new TGeoCombiTrans(7+101-6-2.4-14*i, 0, -0.5, new TGeoRotation("r1", 0, 90, -90)));
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 14; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(101-6-2.4-14*j, 22.5-1.5-3.6-15.15*i, -0.5));
		}
	}
	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(0, 0, -60));

	rear_wall = geom->MakeBox("rear_wall", Iron, 0.5*30, 0.5*45, 0.5*0.5);
	rear_wall->SetLineColor(17);
	cont1 = geom->MakeBox("rear_wall", Iron, 0.5*30, 0.5*45, 0.5*0.5);
	cont1->AddNodeOverlap(rear_wall, 1);

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(-10+7.5*j, -22.5+1.5+3.6+15.15*i, 0.5));
		}
	}
	Top->AddNodeOverlap(cont1, 1, new TGeoCombiTrans(100, 0, -45, new TGeoRotation("r1", 90, 90, 90)));

// Right Wing Wall
	TGeoVolume *rightside_wall = geom->MakeBox("rightside_wall", Iron, 0.5*21.8, 0.5*45, 0.5*0.5);
	rightside_wall->SetLineColor(17);
	cont1 = geom->MakeBox("rightside_wall", Iron, 0.5*21.8, 0.5*20, 0.5*0.5);

	cont1->AddNodeOverlap(rightside_wall, 1);
	for(int i = 0; i < 4; i++)
		cont1->AddNodeOverlap(window, 1, new TGeoTranslation(0, 22.5-0.6-3.6-12.2*i, 0.5));
	Top->AddNodeOverlap(cont1, 1, new TGeoCombiTrans(100+40.6, 0, 10.5, new TGeoRotation("r1", 90, 90, 90)));

	rightside_wall = geom->MakeBox("rightside_wall", Iron, 0.5*30, 0.5*45, 0.5*0.5);
	rightside_wall->SetLineColor(17);
	cont1 = geom->MakeBox("rightside_wall", Iron, 0.5*30, 0.5*45, 0.5*0.5);

	cont1->AddNodeOverlap(rightside_wall, 1);
	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(100+40.6+5, 0, 5));

	
	rightside_wall = geom->MakeBox("rightside_wall", Iron, 0.5*42, 0.5*45, 0.5*0.5);
	rightside_wall->SetLineColor(17);
	cont1 = geom->MakeBox("rightside_wall", Iron, 0.5*42, 0.5*45, 0.5*0.5);

	cont1->AddNodeOverlap(rightside_wall, 1);
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 4; j++){
			cont1->AddNodeOverlap(window, 1, new TGeoTranslation(30-15.4-9*j, -22.5+1.5+2.4+11.4*i, 0.5));
		}
	}
	Top->AddNodeOverlap(cont1, 1, new TGeoCombiTrans(100+40.6+20, 0, -16, new TGeoRotation("r1", 90, 90, 90)));

	rightside_wall = geom->MakeBox("rightside_wall", Iron, 0.5*60, 0.5*45, 0.5*0.5);
	rightside_wall->SetLineColor(17);
	cont1 = geom->MakeBox("rightside_wall", Iron, 0.5*60, 0.5*20, 0.5*0.5);

	cont1->AddNodeOverlap(rightside_wall, 1);

	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(100+30, 0, -36));

// Right Wing Door
	cont1 = geom->MakeBox("cont", Air, 0.5*40, 0.5*40, 0.5*40);
	TGeoVolume *ceil = geom->MakeBox("ceil", Iron, 0.5*5, 0.5*20, 0.5*2);
	ceil->SetLineColor(19);
	
	cont1->AddNodeOverlap(ceil, 1, new TGeoCombiTrans(0, 15, 0, new TGeoRotation("r1", 0, 90, 0)));

	Top->AddNodeOverlap(cont1, 1, new TGeoTranslation(100+21.8+42, -20, -10));

// K
	TGeoCombiTrans *ct_K_1 = new TGeoCombiTrans("ct_K_1", 1, -1, 0, new TGeoRotation("r1", 45, 0, 0));
  TGeoCombiTrans *ct_K_2 = new TGeoCombiTrans("ct_K_2", 1, 1, 0, new TGeoRotation("r1", -45, 0, 0));
  TGeoVolume *K = geom->MakeBox("K", Air, 0.5*5, 0.5*5, 0.5*0.5);
  TGeoVolume *bar1 = geom->MakeBox("bar1", Iron, 0.5*0.5, 0.5*5, 0.5*0.5);
	bar1->SetLineColor(kBlue);
  K->AddNodeOverlap(bar1, 1);
  TGeoVolume *bar2 = geom->MakeBox("bar2", Iron, 0.5*0.5, 0.5*2.5*sq2, 0.5*0.5);
  K->AddNodeOverlap(bar2, 1, ct_K_1);
  K->AddNodeOverlap(bar2, 1, ct_K_2);
	bar2->SetLineColor(kBlue);

// J
  TGeoVolume *J = geom->MakeBox("J", Air, 0.5*5, 0.5*5, 0.5*0.5);
  J->AddNodeOverlap(bar1, 1);
  TGeoPcon *pcon_1 = new TGeoPcon("pcon", -180, 180, 2);
  pcon_1->DefineSection(0, 0, 0.75, 1.25);
  pcon_1->DefineSection(1, 0.5, 0.75, 1.25);
  TGeoVolume *pcon_1_vol = new TGeoVolume("pcon_vol", pcon_1);
	pcon_1_vol->SetLineColor(kBlue);
  J->AddNodeOverlap(pcon_1_vol, 1, new TGeoTranslation(-1, -2.5, 0));
	J->SetLineColor(kGreen);

// G
  TGeoVolume *G = geom->MakeBox("G", Air, 0.5*5, 0.5*5, 0.5*0.5);
  TGeoPcon *pcon_2 = new TGeoPcon("pcon", 30, 300, 2);
  pcon_2->DefineSection(0, 0, 2, 2.5);
  pcon_2->DefineSection(1, 0.5, 2, 2.5);
  TGeoVolume *pcon_2_vol = new TGeoVolume("pcon_vol", pcon_2);
	pcon_2_vol->SetLineColor(kBlue);
  G->AddNodeOverlap(pcon_2_vol, 1, new TGeoTranslation(0, 0, 0));
  TGeoVolume *bar3 = geom->MakeBox("bar3", Iron, 0.5*3, 0.5*0.5, 0.5*0.5);
	bar3->SetLineColor(kBlue);

  G->AddNodeOverlap(bar3, 1, new TGeoTranslation(1, -0.5, 0));
  G->AddNodeOverlap(bar3, 1, new TGeoCombiTrans(1.5, -2, 0, new TGeoRotation("r1", 90, 0, 0)));
	G->SetLineColor(kBlue);

	Top->AddNodeOverlap(K, 1, new TGeoTranslation(-10, 22.5+8, 24));
	Top->AddNodeOverlap(J, 1, new TGeoTranslation(0, 22.5+8, 24));
	Top->AddNodeOverlap(G, 1, new TGeoTranslation(9, 22.5+8, 24));

	Top->Draw("ogl");
}
