import { ApiProperty } from '@nestjs/swagger';
import { Column, Entity } from 'typeorm';

@Entity()
export class BadRequest {
  @ApiProperty()
  @Column()
  statusCode: number;

  @ApiProperty()
  @Column()
  timestamp: string;

  @ApiProperty()
  @Column()
  path: string;

  @ApiProperty()
  @Column()
  error: string;
}
