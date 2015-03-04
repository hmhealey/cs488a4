require('buckyball')
require('readobj')

water = gr.material({30 / 255, 144 / 255, 255 / 255}, {0.4, 0.4, 0.4}, 25)
sand = gr.material({255 / 255, 250 / 255, 205 / 255}, {0.0, 0.0, 0.0}, 0)
wood = gr.material({139 / 255, 90 / 255, 43 / 255}, {0.3, 0.3, 0.3}, 40)
leaf = gr.material({0, 205 / 255, 0}, {0.2, 0.4, 0.2}, 25)
purple = gr.material({0.5, 0, 1}, {0.7, 0.7, 0.7}, 25)
grey = gr.material({0.4, 0.4, 0.5}, {0.4, 0.4, 0.4}, 40)

scene = gr.node('scene')

-- water
plane = gr.mesh('plane', {
    {-1, 0, -1},
    {1, 0, -1},
    {1,  0, 1},
    {-1, 0, 1}
}, {
    {3, 2, 1, 0}
})
plane:set_material(water)
plane:scale(30, 30, 30)
scene:add_child(plane)

-- island
island = gr.sphere('island')
island:set_material(sand)
island:translate(0, -50, 0)
island:scale(40, 51, 40)
scene:add_child(island)

-- cow!
cow = gr.mesh('cow', readobj('cow.obj'))
cow:set_material(purple)
cow:rotate('z', 7)
cow:translate(-3, 2, 3)
cow:scale(0.3, 0.3, 0.3)
scene:add_child(cow)

-- "sharks"
-- I'd reuse the cow mesh we already loaded, but I want different colours (so we need different mesh objects)
-- and for some reason I can't store the results of readobj in a separate variable
shark_mesh = gr.mesh('shark_mesh', readobj('cow.obj'))
shark_mesh:set_material(grey)
shark_mesh:scale(0.1, 0.1, 0.1)

shark1 = gr.node('shark1')
shark1:add_child(shark_mesh)
shark1:translate(1.5, -0.1, 10)
shark1:rotate('y', 200)
scene:add_child(shark1)

shark2 = gr.node('shark2')
shark2:add_child(shark_mesh)
shark2:translate(-2, 0, 10)
shark2:rotate('y', -30)
scene:add_child(shark2)

-- the tree trunk
trunk1 = gr.node('trunk1')
trunk1:translate(2, 1, 4)
scene:add_child(trunk1)

s1 = gr.sphere('s1')
s1:set_material(wood)
s1:scale(0.7, 1, 0.7)
trunk1:add_child(s1)

trunk2 = gr.node('trunk2')
trunk2:translate(-0.1, 1, 0)
trunk2:rotate('z', 4)
trunk1:add_child(trunk2)

s2 = gr.sphere('s2')
s2:set_material(wood)
s2:scale(0.65, 0.85, 0.65)
trunk2:add_child(s2)

trunk3 = gr.node('trunk3')
trunk3:translate(-0.1, 0.8, 0)
trunk3:rotate('z', 4)
trunk2:add_child(trunk3)

s3 = gr.sphere('s3')
s3:set_material(wood)
s3:scale(0.6, 0.75, 0.6)
trunk3:add_child(s3)

trunk4 = gr.node('trunk4')
trunk4:translate(-0.1, 0.6, 0)
trunk4:rotate('z', 7)
trunk3:add_child(trunk4)

s4 = gr.sphere('s4')
s4:set_material(wood)
s4:scale(0.55, 0.65, 0.55)
trunk4:add_child(s4)

trunk5 = gr.node('trunk5')
trunk5:translate(-0.1, 0.4, 0)
trunk5:rotate('z', 10)
trunk4:add_child(trunk5)

s5 = gr.sphere('s5')
s5:set_material(wood)
s5:scale(0.5, 0.55, 0.5)
trunk5:add_child(s5)

-- the leaves
leaf_root = gr.node('leaf_root')

leaf_part1 = gr.node('leaf_part1')
leaf_part1:translate(0.4, 0.3, 0)
leaf_part1:rotate('z', 30)
leaf_root:add_child(leaf_part1)

leaf_c1 = gr.cube('leaf_c1')
leaf_c1:set_material(leaf)
leaf_c1:scale(1, 0.2, 1)
leaf_c1:translate(0, 0, -0.5)
leaf_part1:add_child(leaf_c1)

leaf_part2 = gr.node('leaf_part2')
leaf_part2:translate(0.9, 0, 0)
leaf_part2:rotate('z', -30)
leaf_part1:add_child(leaf_part2)

leaf_c2 = gr.cube('leaf_c2')
leaf_c2:set_material(leaf)
leaf_c2:scale(1, 0.2, 1)
leaf_c2:translate(0, 0, -0.5)
leaf_part2:add_child(leaf_c2)

leaf_part3 = gr.node('leaf_part3')
leaf_part3:translate(0.9, 0, 0)
leaf_part3:rotate('z', -30)
leaf_part2:add_child(leaf_part3)

leaf_c3 = gr.cube('leaf_c3')
leaf_c3:set_material(leaf)
leaf_c3:scale(1, 0.2, 1)
leaf_c3:translate(0, 0, -0.5)
leaf_part3:add_child(leaf_c3)

leaf_count = 7
for i=0, leaf_count do
    leaf = gr.node('leaf' .. i)
    leaf:add_child(leaf_root)
    leaf:rotate('y', i * 360 / leaf_count)
    trunk5:add_child(leaf)
end

-- the rock
buckyball:set_material(grey)
buckyball:scale(1.2, 1.2, 1.2)
buckyball:translate(-1, 2, -2)
scene:add_child(buckyball)

-- the lights
l1 = gr.light({200, 200, 600}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene, 'island.png', 1024, 1024,
    {0, 2, 15}, {0, 0, -1}, {0, 1, 0}, 50,
    {0.5, 0.5, 0.5}, {l1})

--gr.render(scene, 'island_topdown.png', 512, 512,
--    {0, 25, 0}, {0, -1, 0}, {0, 0, -1}, 50,
--    {0.5, 0.5, 0.5}, {l1})
