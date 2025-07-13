# OOP-Project-Part2
<div>
  <h3>A part 2 continuation from OOP_project.</h3>
    <p>Basically added more features to the freight and cargo scheduler C++ CLI application</p>
  <h2>Main highlights</h2>
    <ol>
      <li>Demonstates OOP SOLID principles</li>
      <li>FreightRecords and CargoRecords use the builder design pattern by employing addRecord, modifyRecord and displayRecord interface classes</li>
      <li>Scheduler use the strategy design pattern by employing scheduleStrategy interface, and scheduleByTime & scheduleByCapacity concrete starategies</li>
      <li>Mainprogram only declares builder and strategy objects appropriately in the necessary menu blocks, eliminating global variables.</li>
    </ol>
  <h2>What's different from part 1?</h2>
   <ol>
      <li>Freight has 3 types of capacity, minimover (2), cargocruiser (6), megacruiser (12)</li>
      <li>Cargo with the same ID, destination and time can contain up to 10 duplicates</li>
      <li>Scheduler can generate schedule either by maximising capacity, or by priortizing arrival time</li>
    </ol>
</div>
